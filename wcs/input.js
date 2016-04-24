var coordinates = function(element) {
    element = $(element);
    var top = element.position().top;
    var left = element.position().left;
    $('#results').text('X: ' + left + ' ' + 'Y: ' + top);
}


$('#box').draggable({
    start: function() {
        coordinates('#box');
    },
    stop: function() {
        coordinates('#box');
    }
});