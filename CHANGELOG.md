Changelog
=========
2.4.0 (2020-09-22)
- Built with Xcode 12 GM seed
- Added support for Universal Links
- Added target content identifier to notification model
- Use notification title (when present) in UIAlertController or UIViewController instead of app name
- Added new events for unknown notifications in background and foreground
- Added markAllAsRead in InboxManager

2.3.0 (2020-06-18)
- Added new unlaunch method
- Added possibility to send notification not shown in the inbox
- Added possibility to expire inbox items
- Added new property type in NotificareDeviceInbox model
- Added new properties in Notificare.plist under OPTIONS for Light/Dark mode
- Minor bug fixes and improvements
- Built against tvOS 13.4 SDK

2.2.1 (2019-11-14)
- Changed Notificare and NotificareActions class delegates to strong references

2.2.0 (2019-10-08)
- Built for tvOS 13 (Xcode 11 required)
- Added clearDeviceLocation method and DISABLE_LOCATION_SERVICES plist property
- Fixed issue with launchOptions

2.1.0 (2019-04-30)
- Added helper method to retrieve controller for notification
- Added new delegate method didChangeNotificationSettings

2.0.0-beta (2018-04-10)
- Initial beta release

