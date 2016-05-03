$(function() {
			$( "#slider-temp" ).slider({
				range: "max",
				min: 75,
				max: 110,
				value: 80,
				slide: function( event, ui ) {
					$( "#temp" ).val( ui.value );
				}
			});
			$( "#temp" ).val( $( "#slider-temp" ).slider( "value" ) );
});

$(function() {
			$( "#slider-y" ).slider({
				orientation: "vertical",
				range: "max",
				min: 0,
				max: 100,
				value: 100,
				slide: function( event, ui ) {
					$( "#y" ).val( 100 - ui.value );
				}
			});
			$( "#y" ).val( $( "#slider-y" ).slider( "value" ) );
});