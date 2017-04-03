(function ($) {
    // implementing as a function
    // $.fn.ajaxRefresh = function(data) {
    //     alert('Total random titles: ' + data);
    // };

    // implementing as behaviour
    Drupal.behaviors.project18 = {
        attach: function (context, settings) {
            $('body').once(function() {
                var $dialog = $("<div id='ajax_dialog'></div>");
                $dialog.attr('title', 'Project 18 dialog');
                $(this).prepend($dialog);
            });
            if (settings.total) {
                // alert(settings.total)
                // jquery UI dialog
                $("#ajax_dialog")
                    .html('<p>Total random titles: '+settings.total+'</p>')
                    .dialog();
            }
        }
    };
})(jQuery);
