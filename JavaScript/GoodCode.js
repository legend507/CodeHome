// falsy value
 underfined, null, 0, false, NaN, ''

// random number of array
var items = [12, 548 , 'a' , 2 , 5478 , 'foo' , 8852, , 'Doe' , 2145 , 119];
var randomItem = items[Math.floor(Math.random() * items.length)];

var x = Math.floor(Math.random() * (max - min + 1)) + min;

// Detecting an undefined object property
if (typeof something === "undefined") {
    alert("something is undefined");
}
    //If an object variable which have some properties you can use same thing like this:
if (typeof my_obj.someproperties === "undefined"){
    console.log('the property is not available...'); // print into console
}

//Avoid null comparisons, unless null value is specifically assigned

//Bad
function(items){
    if(items != null){
        items.sort();
    }
    //Will work with:
    //var items = true;
    //var items = 1;
    //var items = "blah";   
}

function(items){
    if(items != null){
        items.sort();
    }
    //Will work with:
    //var items = true;
    //var items = 1;
    //var items = "blah";   
}

//Better communicate your intention and prevent false positive with:
function(items){
    if(items instanceof Array){
        items.sort();
    }
}

function(items){
    if(items instanceof Array){
        items.sort();
    }
}

/*
instanceof to test for specific object types
- object instanceof MyType
- typeof to test for primitive types
- typeof value == "string"
- BEWARE typeof null == object
*/
//Contrary to common belief, "undefined" is NOT a keyword in JavaScript and can in fact have a value assigned to it.
// Degenerate code. DO NOT USE.
var undefined = false;  // Shockingly, this is completely legal!
if (myVar === undefined) {
    alert("You have been misled. Run away!");
}

// convert arguments into native javascript array
var args = Array.prototype.slice.call(arguments, 0);

//add strim function into String
String.prototype.trim = function () {
	return this.replace(/^\s+|\s+$/g, "");
};

// append one array into another array
var array1 = [12 , "foo" , {name: "Joe"} , -2458]; 
var array2 = ["Doe" , 555 , 100];
Array.prototype.push.apply(array1, array2);

//
function isNumber(n){
	return !isNaN(parseFloat(n)) && isFinite(n);
}

//
function isArray(obj){
	return Object.prototype.toString.call(obj) === '[object Array]';
}

//Get the min and max value of array
var numbers= [5, 458 , 120 , -215 , 228 , 400 , 122205, -85411];
var maxInNumbers = Math.max.apply(Math, numbers);
var minInNumbers = Math.min.apply(Math, numbers);

//clear the array
var myArray = [12, 222, 1000];
myArray.length = 0;

// delete one element of array
var items = [12, 548 ,'a' , 2 , 5478 , 'foo' , 8852, , 'Doe' ,2154 , 119 ];
items.length; // return 11
items.splice(3,1) ;
items.length; // return 10
/* items will be equal to [12, 548, "a", 5478, "foo", 8852, undefined × 1, "Doe", 2154,       119]   */

// use map function to iterate the array
var square = [1, 2, 3, 5].map(function(val){
	return val*val;
});

// avoid for in to iterate the array
var sum = 0;
for (var i = 0, len = arrayNum.length; i < len; ++i){
	sum += arrayNum[i];
}

// replace if else with switch case
function getCategory(age) {  
    var category = "";  
    switch (true) {  
        case isNaN(age):  
            category = "not an age";  
            break;  
        case (age >= 50):  
            category = "Old";  
            break;  
        case (age <= 20):  
            category = "Baby";  
            break;  
        default:  
            category = "Young";  
            break;  
    };  
    return category;  
}  

var person = {name :'Saad', age : 26, department : {ID : 15, name : "R&D"} };
var stringFromPerson = JSON.stringify(person);
/* stringFromPerson  "{"name":"Saad","age":26,"department":{"ID":15,"name":"R&D"}}"   */
var personFromString = JSON.parse(stringFromPerson);

setInterval(doSomethingPeriodically, 1000);  
setTimeout(doSomethingAfterFiveSeconds, 5000);

// comma symbol
var a = 0; 
var b = ( a++, 99 ); 
console.log(a);  // a will be equal to 1 
console.log(b);  // b is equal to 99

//1. Failed to save page in web browser
<noscript> <iframe src="*.html"></iframe></noscript>

//2. prevent frame or iframe be contained by others
<script language="javascript">
	if (top.location != self.location)
		top.location = self.location
</script>

//3. Do not alert the script errors
<script language="javascript">
	function killErrors(){
		return true;
	}

	window.onerror = killErrors;
</script>

//4. display the latest update time autumatically
<script language="javascript">
	document.write("The last modify date :" + document.lastModified + "")
</script>
