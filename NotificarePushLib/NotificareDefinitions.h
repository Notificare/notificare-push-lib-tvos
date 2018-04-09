//
//  NotificareDefinitions.h
//  NotificarePushLib
//
//  Created by Joel Oliveira on 19/10/2017.
//  Copyright © 2017 Notificare. All rights reserved.
//

#import <UIKit/UIKit.h>

#ifndef NotificareDefinitions_h
#define NotificareDefinitions_h

#define kSDKVersion @"2.0.0"
#define kOSVersion [[UIDevice currentDevice] systemVersion]
#define kDaysInterval 1
#define kLocationSessionBackoffDistance 7.0
#define kAuthProtocol @"https"
#define kUseSSL YES

#define kNotificareNewRegistration @"notificareNewRegistration"
#define kNotificareSessionDate @"notificareSessionDate"
#define kNotificareRegisteredForNotifications @"notificareRegisteredForNotifications"
#define kNotificareAllowedUI @"notificareAllowedUI"
#define kNotificareUserID @"notificareUserID"
#define kNotificareUserName @"notificareUserName"
#define kNotificareDeviceToken @"notificareDeviceToken"
#define kNotificareDeviceTokenData @"notificareDeviceTokenData"
#define kNotificareDeviceCountry @"notificareDeviceCountry"
#define kNotificareDeviceCountryCode @"notificareDeviceCountryCode"
#define kNotificareAllowedLocationServices @"notificareAllowedLocationServices"
#define kNotificareLocationServicesAuthStatus @"notificareLocationServicesAuthStatus"
#define kNotificareDeviceTimezone @"notificareDeviceTimezone"
#define kNotificareOSVersion @"notificareOSVersion"
#define kNotificareSDKVersion @"notificareSDKVersion"
#define kNotificareAppVersion @"notificareAppVersion"
#define kNotificareDeviceModel @"notificareDeviceModel"
#define kNotificareDeviceLanguage @"notificareDeviceLanguage"
#define kNotificareDeviceDnD @"notificareDeviceDnD"
#define kNotificareDeviceUserData @"notificareDeviceUserData"
#define kNotificareDeviceLatitude @"notificareDeviceLatitude"
#define kNotificareDeviceLongitude @"notificareDeviceLongitude"
#define kNotificareDeviceFloor @"notificareDeviceFloor"
#define kNotificareDeviceLastRegistered @"notificareDeviceLastRegistered"
#define kNotificareBackgroundAppRefresh @"notificareBackgroundAppRefresh"
#define kNotificareBluetoothON @"notificareBluetoothON"
#define kNotificareDeviceTransport @"notificareDeviceTransport"

#define kNotificareInboxBadge @"NotificareInboxBadge"

#define kNotificareErrorStack @"notificareErrorStack"

#define kNotificareMigrationCheck @"notificareMigrationCheckV2"

#endif /* NotificareDefinitions_h */
