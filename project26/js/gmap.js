(function ($) {
    Drupal.behaviors.project26 = {
        attach: function (context, settings) {
            var data = settings.project26.data;

            function initMap() {
                // used if no markers provided, Kyiv
                var defaultCenter = {lat: 50.4501, lng: 30.5234};

                var map = new google.maps.Map(document.getElementById(data.map_id), {
                    center: defaultCenter,
                    zoom: 10
                });

                var markers = [];
                // create marked from the passed data
                $.each(data.markers, function (index, value) {
                    var position = {
                        lat: value.lat,
                        lng: value.lng
                    };

                    var marker = new google.maps.Marker({
                        position: position,
                        map: map,
                        title: value.title
                    });

                    // load node teaser on marker click
                    marker.addListener('click', function () {
                        $.get(data.ajax_url + value.nid, function (data) {
                            var infowindow = new google.maps.InfoWindow({
                                content: data
                            });

                            infowindow.open(map, marker);
                        });
                    });

                    markers.push(marker);
                });

                // fit multiple markers
                if (data.markers.length > 1) {
                    var bounds = new google.maps.LatLngBounds();

                    $.each(markers, function (index, marker) {
                        bounds.extend(marker.position);
                    });

                    map.fitBounds(bounds);
                } else if (data.markers.length === 1) {
                    map.setCenter(markers[0].position);
                }

                // filter and hide markers
                $('#' + data.filter_id).keyup(function () {
                    var filter = $(this).val();
                    $.each(markers, function (index, value) {
                        var re = new RegExp(filter, 'i');

                        if (!value.title.match(re)) {
                            value.setVisible(false);
                        } else {
                            value.setVisible(true);
                        }
                    })
                });
            }

            initMap();
        }
    };

})(jQuery);
