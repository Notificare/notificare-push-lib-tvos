# Migration

## From 2.3.x to 2.4.0

When migrating from 2.3.0 you should use Xcode 12 with support for tvOS 14. There are few changes to take into account but some adjustments are needed to fully support this new version.

### Remote Notifications
We've made some changes in how you can receive data from notifications sent from unknown sources. More specifically, you will now have two new delegates:

```
- (void)notificarePushLib:(NotificarePushLib *)library didReceiveUnknownNotificationInBackground:(NSDictionary *)notification;

- (void)notificarePushLib:(NotificarePushLib *)library didReceiveUnknownNotificationInForeground:(NSDictionary *)notification;
```
These will be triggered accordingly when users receive remote or local notifications from unknown sources.

### Inbox
A new method is now available to allow you to mark all inbox items as read with a single operation:

```
[[[NotificarePushLib shared] inboxManager] markAllAsRead:^(id  _Nullable response, NSError * _Nullable error) {

}];
```

### Universal Links
In this version we will also provide support for universal links. These are links you create in our dashboard that allow you to deep link to certain areas of your app from web pages or email and SMS messages. When using the App Delegate Proxy, these will be automatically handled for you as long as you add the Associated Domains capability with the following entry:

```
applinks:YOUR_PREFIX.ntc.re
```

Then if all Links of type ```dynamic links``` you create will trigger the usual delegate where you handle all the deep links for your app (when clicked from web pages or email and SMS messages):

```
-(BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options{
    [[NotificarePushLib shared]  handleOpenURL:url withOptions:options];
    // Handle the deep links 
    
    return YES;
}
```

If you are not using the App Delegate Proxy, you will also need to implement the following delegate and corresponding helper method:

```
- (BOOL)application:(UIApplication *)application continueUserActivity:(NSUserActivity *)userActivity restorationHandler:(void (^)(NSArray<id<UIUserActivityRestoring>> * _Nullable))restorationHandler{
    [[NotificarePushLib shared] continueUserActivity:userActivity restorationHandler:restorationHandler];
}
```

For apps using UIScene or SwiftUI the following method is needed (independently if you use App Delegate Proxy or not) instead:

```
- (void)scene:(UIScene *)scene continueUserActivity:(NSUserActivity *)userActivity{
    [[NotificarePushLib shared] continueUserActivity:userActivity];
}
```

Finally you can also retrieve the underlying URL Scheme added to a Dynamic Link by using the method:

```
[[NotificarePushLib shared] fetchLink:YOUR_NS_URL completionHandler:^(id  _Nullable response, NSError * _Nullable error) {
    // Response will be a NSURL containing the iOS URL added to the Dynamic Link
}];
```

## From 2.x.x to 2.3.0

When migrating from older version of v2 to 2.3.0 there isn't much you need to take into account. This version is built against tvOS SDK 13.4 and should be used with Xcode 11.5.

### Initialization

There is now one new method that allows you to opt-out a device from Notificare. For those cases where you want to completly remove all data of a device from Notificare, you can use this method as follows:

```
[[NotificarePushLib shared] unlaunch];
```

This is basically the opposite of  the  ```launch``` method. Once invoked, all data will be deleted from Notificare and attamept to use any other methods from Notificare will fail. After using this method the only way to start using Notificare again is by invoking:

```
[[NotificarePushLib shared] launch];
```

### Remote Notifications

There are not relevant changes on this on remote notifications, other than some overhauling in Inbox functionalities. Although implementation remains exactly the same, the inbox functionality in 2.3.0 introduces new features like visibility and expiration which require absolutely no changes in your implementation. Additionally, inbox items will also include information about the type of notification it was sent. This results in the following new properties added to the NotificareDeviceInbox model:

- type
- visible
- expires

It is also worth mentioning that the following delegates:

```
-(void)notificarePushLib:(NotificarePushLib *)library didLoadInbox:(nonnull NSArray<NotificareDeviceInbox *> *)items{

}

- (void)notificarePushLib:(NotificarePushLib *)library didUpdateBadge:(int)badge{
  
}
```

Will be called more often in this version, namely everytime the app enters in foreground and after invoking any method in this class. If you rely on these (and you probably are), you should take that into account.

### Miscelaneous

This version also includes 2 new objects in the Notificare.plist under OPTIONS. We've added the possibility to configure notification's UI for Light/Dark mode. When present, we will use those instead to apply UI styles. If not present, we will keep using the default properties as in previous versions. 

## From 1.x.x to 2.0.0

If you are migrating from 1.x.x version of our SDK, there are several breaking changes that you will need to take into consideration. A considerable part of the API in version 1 was removed and replaced with a simplified new API that unifies integration of remote notifications, location services, contextual content and analytics for tvOS 10 and up.

Guides for setup and implementation can be found here:

https://docs.notifica.re/sdk/v2/tvos/setup/



## Initialization
A few changes were introduces when initializing the library, mainly a new method is required to initialize the library (where you can override Notificare.plist app keys). This creates a clear separation between the moment you initialize our SDK and when you actually want to start using it.

You can find more information about initialization here:

https://docs.notifica.re/sdk/v2/tvos/implementation/ 

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

