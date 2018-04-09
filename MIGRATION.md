# Migration

If you are migrating from 1.x.x version of our SDK, there are several breaking changes that you will need to take into consideration. A considerable part of the API in version 1 was removed and replaced with a simplified new API that unifies integration of remote notifications, location services, contextual content and analytics for tvOS 10 and up.

Guides for setup and implementation can be found here:

https://docs.notifica.re/sdk/v2/tvos/setup/


## Device Registration

When you are migrating from older versions, you will notice that you no longer need to take action whenever a device token is registered, as device registration in SDK 2.0 is totally managed by Notificare. You can still register/unregister a device to/from a userID and userName and Notificare will always keep that information cached in the device. This will make sure that whenever a device token changes everything is correctly handled without the need for your app to handle it. 

It is also important to mention that the first time an app is launched we will assign a UUID token to the device before you even request to register for notifications. Basically with this new SDK all features of Notificare can still be used even if your app does not implement remote notifications. Obviously if you never request to register for notifications, users will never receive remote notifications, although messages will still be in the inbox (if implemented), tags can be registered, location services can be used and pretty much all features will work as expected.

Once you decide to register for notifications, those automatically assigned device tokens will be replaced by the APNS tokens assign to each device. 

Bottom line, for this version you should remove all the device registration delegates used in previous versions and optionally you can implement the new delegates which are merely informative. You can find more information about device registration here:

https://docs.notifica.re/sdk/v2/ios/implementation/register/ 

## Remote Notifications

In SDK 2.0, we've unified notification handling to work as one for all versions since tvOS 10. We've also simplified the implementation of this functionality by allowing you to take actions for 2 different situations, when notifications are received in foreground or background. 

Basically for this version you should remove all the notification delegates implemented for previous versions and implement only the following delegates:

```
-(void)notificarePushLib:(NotificarePushLib *)library didReceiveRemoteNotificationInForeground:(nonnull NotificareNotification *)notification withController:(id _Nullable)controller {
 //A notification arrived while the app is being used you can choose to interrupt the user or simply show an in-app badge
}
```

```
-(void)notificarePushLib:(NotificarePushLib *)library didReceiveRemoteNotificationInBackground:(nonnull NotificareNotification *)notification withController:(id _Nullable)controller{
  //Notification arrived in background and user clicked your app icon, it is a good moment to present the notification
}
```

Additionally you've also changed the way notifications should be presented, by allowing you to provide us a navigation controller which we should use to present the UI controllers you received in the previous delegates. This will allow you to have more control over how notifications are shown and how you customise the navigation controller where we will stack notification controllers. This must be done by using the following method:

```
-(void)notificarePushLib:(NotificarePushLib *)library didReceiveRemoteNotificationInBackground:(nonnull NotificareNotification *)notification withController:(id _Nullable)controller{
	UINavigationController *navController = (UINavigationController *)self.window.rootViewController;
	[[NotificarePushLib shared] presentNotification:notification inNavigationController:navController withController:controller];
}
```

Another important thing to acknowledge for this new version is the fact that we've unified the local and remote message inbox under a new class, called inboxManager. You will need to change your current inbox implementation to reflect these changes in order to benefit from a super optimised cached version of your messages. 

More in-depth guides can be found here:

https://docs.notifica.re/sdk/v2/tvos/implementation/push/

## Location Services

In this new version, locations services do not suffer any significant API change. Most of the changes to this functionality are under-the-hood and implementation for previous versions will work in this new versions.

For more information, please read the guides for this functionality located here:

https://docs.notifica.re/sdk/v2/tvos/implementation/location-services/

## Tags

This functionality remains pretty much the same in this new version. We did add two new methods that you might find interesting when implementing tags. 

You can now add a single tag using the following method:

```
[[NotificarePushLib shared] addTag:@"tag_press" completionHandler:^(id  _Nullable response, NSError * _Nullable error) {
	if (!error) {
		//Tag added
	}
}];
```

And you can remove several tags with one single request by using the method below:

```
[[NotificarePushLib shared] removeTags:@[@"tag_press", @"tag_news"] completionHandler:^(id  _Nullable response, NSError * _Nullable error) {
	if (!error) {
		//Tags removed
	}
}];
```
 
You can find more information in our guides located here:

https://docs.notifica.re/sdk/v2/tvos/implementation/tags/

## Monetize

This functionality did not suffer any change in SDK 2.0 and you will not need to change anything in your current implementation.

More in-depth information can be found in our guides located here:

https://docs.notifica.re/sdk/v2/tvos/implementation/monetize/implementation/

## Analytics

This functionality did not suffer any change in SDK 2.0 and you will not need to change anything in your current implementation.

More in-depth information can be found in our guides located here:

https://docs.notifica.re/sdk/v2/tvos/implementation/analytics/

## Storage

This functionality did not suffer any change in SDK 2.0 and you will not need to change anything in your current implementation.

More in-depth information can be found in our guides located here:

https://docs.notifica.re/sdk/v2/tvos/implementation/storage/

