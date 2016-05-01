function converter(oldValue, oldMax, oldMin, newMax, newMin) {
	var oldRange = oldMax - oldMin;
	var newRange = newMax - newMin;
	var newValue = (((oldValue - oldMin) * newRange) / oldRange) + newMin;
	return Math.round(newValue);
}

showerForm = document.forms['shower'];

var coordinates = function(element) {
    element = $(element);
    var top = element.position().top;
	var realTop = converter(top, 250, 0, 50, -50);
    var left = element.position().left;
	var realLeft = converter(left, 450, 0, 100, 0);
	showerForm.elements["z"].value = realLeft;
	showerForm.elements["x"].value = realTop;
}


$('#box').draggable({
	
	containment: "#canvas",
	
    start: function() {
        coordinates('#box');
    },
    stop: function() {
        coordinates('#box');
    }
});