(function(){
'use strict';

  angular
      .module('yapkiApp', ['ngMaterial', 'users'])
      .config( function($mdThemingProvider, $mdIconProvider) {

      $mdIconProvider
        .defaultIconSet("assets/svg/avatars.svg", 128 )
        .icon("menu", "assets/svg/ic_menu_24px.svg", 24);


        // Use the 'brown' theme - override default 'blue' theme
        //$mdThemingProvider.theme('default')
        //  .primaryPalette('brown')
        //  .accentPalette('red');

      });

})();
