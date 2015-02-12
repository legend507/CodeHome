'use strict';

/**
 * dependencies
 */
var amqp = require('amqplib'),
	when = require('when');


/**
 * Sender Class, initialized with amqp address
 * @param {string} amqpAddr The amqp address
 * @param {number} retryDelay A delay time per milliseconds 
 * @constructor
 */
var Sender = function( amqpAddr, retryDelay ) {
	/**
	 * amqp address
	 * @type {!string}
	 * @private
	 */
	this.addr_ = amqpAddr || 'amqp://localhost';
	/**
	 * amqp channel
	 * @type {Object}
	 * @private
	 */
	this.ch_ = null;
	/**
	 * amqp connection
	 * @type {Object}
	 * @private
	 */	
	this.con_ = null;

	this.ex_ = 'BS';

	this.retryDelay_ = retryDelay;

	this.tryConnect_( retryDelay );
};

/**
 * create channel to amqp.
 * @param {Object} con Amqp connection
 * @private
 */
Sender.prototype.createChannel_ = function( con ) {
	this.con_ = con;
	return this.con_.createConfirmChannel();
};

/**
 * create exchange for amqp in direct way.
 * @param {Object} ch Amqp channel
 * @private
 */
Sender.prototype.createExchange_ = function( ch ) {
	this.ch_ = ch;
	return this.ch_.assertExchange( this.ex_ , 'direct', { durable: true } );
};


/**
 * Handle unrouteable message
 * @private
 */
Sender.prototype.handleUnrouteableMessages_ = function() {
	return this.ch_.on('return', function( msg ) {
		return console.log( 'Message returned to sender ' + msg.content );
	});
};

/**
 * Handle amqp disconenction and try to reconnect.
 * @private
 */
Sender.prototype.handleDisconnections_ = function() {
	return this.con_.on('error', (function( that ) {
		return function( err ) {
			return that.retryConnect_( that.retryDelay_ , err );
		};
	})(this));
};

/**
 * publish message to amqp  
 * @param {string} key An argument that represent routing key.
 * @param {object} msg Message wrapped by protocol buffer.  
 * @private
 */
Sender.prototype.publish_ = function( key, msg ) {
	var self = this;

	this.ch_.publish( this.ex_, key, msg, { deliveryMode: 2, mandatory: true }, function() {
		console.log('message processed');
		return self.ch_.close();
	});
};

/**
 * deliver message to amqp
 * @param {string} key An argument that represent routing key.
 * @param {object} msg Message wrapped by protocol buffer.
 * @public
 */
Sender.prototype.deliverMessage = function ( key, msg ) {
	return this
		.tryConnect_( this.retryDelay_ )
		.with(this)
		.done(function() {
			return this.publish_( key, msg );
		});
}

/**
 * retry connect to amqp.
 * @param {number} retryDelay A delay time per milliseconds
 * @param {Object} err Error object
 * @private
 */
Sender.prototype.retryConnect_ = function( retryDelay, err ) {
	console.error('MessageBus disconnected, attempted to reconnect' + err);
	return when( 'retry' )
		.with( this )
		.delay( retryDelay )
		.then(function() { 
			return this.tryConnect_( this.retryDelay_ ); 
		});
}

/**
 * Try to connect to amqp.
 * @private
 */
Sender.prototype.tryConnect_ = function( retryDelay ) {
	return when(amqp.connect( this.addr_ ))
		.with( this )
		.then( this.createChannel_ )
		.then( this.createExchange_ )
		.then( this.handleUnrouteableMessages_ )
		.then( this.handleDisconnections_ )
		.catch( function( e ) {
			return this.retryConnect_( retryDelay, e );
		});
};

/**
 * exports
 */
module.exports = exports = Sender;