/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/**
 * Created by mwn on 13/12/14.
 */

var YafraIonicGpsCtrl = angular.module('YafraApp.controller-gps', []);


/**
 * A google map / GPS controller.
 */
YafraIonicGpsCtrl.controller('GpsCtrl', ['$scope', '$state', 'SysMsg', function ($scope, $state, SysMsg) {
    'user strict';

    /**
     * Get GPS coordinates once - works on mobile and browsers
     */
    // get GPS location once
    $scope.gpsonce = function () {
        SysMsg.debug("new gps: get updated GPS location now");
        navigator.geolocation.getCurrentPosition(onGpsSuccess, onGpsError, getGpsOptions);
    };


    /**
     * Get GPS coordinates constantly - works on mobile and only during active app / foreground mode - does not work if app is closed due to battery constraints
     */
    // classic background GPS watch
    $scope.gpsbackground = function (gps) {
        SysMsg.debug("gps background with toggle value: " + gps.toggle);
        if (gps.toggle == "true") {
            navigator.geolocation.clearWatch($rootScope.gpswatchid);
            $rootScope.gpswatchid = navigator.geolocation.watchPosition(onGpsSuccess, onGpsError, getGpsOptions);
            $scope.gpsmessage = 'GPS START - Sende nun GPS Daten bis auf weiteres';
        } else {
            if ($rootScope.gpswatchid != null) {
                navigator.geolocation.clearWatch($rootScope.gpswatchid);
                $scope.gpsmessage = 'GPS STOP - GPS Uebermittlung angehalten';
            }
        }
    };
    function onGpsSuccess(position) {
        var c = position.coords;
        $scope.position = position;
        if ($rootScope.lastlat == c.latitude && $rootScope.lastlon == c.longitude) {
            $scope.gpsmessage = 'GPS Position glyych blyybe';
            return;
        }
        $rootScope.lastlat = c.latitude;
        $rootScope.lastlon = c.longitude;
        SysMsg.debug("new gps: gps coords: " + c.latitude + " " + c.longitude);
        GPSget($scope.mcbuser.oauthAccessToken).update({'gpslat': c.latitude, 'gpslon': c.longitude},
            function (response) {
                $scope.gpsmessage = 'GPS Position übermittelt';
                SysMsg.debug("new gps: gps send to server OK");
            },
            function (error) {
                SysMsg.debug("new gps: gps send to server (REST) status ERROR: " + error.status);
                $scope.gpsmessage = 'Fehler beim Uebermitteln der GPS Position';
            }
        );
    }
    // geolocation CALLBACK ERROR
    function onGpsError(error) {
        $scope.gpsmessage = 'Fehler beim GPS Signal aufgetreten';
    }

}]);
