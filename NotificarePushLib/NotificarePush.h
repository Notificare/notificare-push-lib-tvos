//
//  NotificarePush.h
//  NotificarePushLib
//
//  Created by Joel Oliveira on 18/10/2017.
//  Copyright © 2017 Notificare. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UserNotifications/UserNotifications.h>
#import "Notificare.h"
#import "NotificareActions.h"
#import "NotificareNotification.h"
#import "NotificareAction.h"
#import "NotificareDeviceInbox.h"
#import "NotificareDefinitions.h"

NS_ASSUME_NONNULL_BEGIN

typedef void (^SuccessNotificationBlock)(NotificareNotification * notification);
typedef void (^SuccessActionBlock)(NotificareAction * action);
typedef void (^SuccessReplyBlock)(NSDictionary * response);
typedef void (^ErrorNotificationBlock)(NSError * error);
typedef void (^ErrorReplyBlock)(NSError * error);

@class NotificarePush;

@protocol NotificarePushDelegate

@optional


- (void)notificarePush:(NotificarePush *)notificarePush didReceiveLaunchURL:(NSURL *)launchURL;

- (void)notificarePush:(NotificarePush *)notificarePush didReceiveRemoteNotificationInBackground:(NotificareNotification *)notification withController:(id _Nullable)controller;

- (void)notificarePush:(NotificarePush *)notificarePush didReceiveRemoteNotificationInForeground:(NotificareNotification *)notification withController:(id _Nullable)controller;

- (void)notificarePush:(NotificarePush *)notificarePush didReceiveUnknownNotification:(NSDictionary *)notification;

- (void)notificarePush:(NotificarePush *)notificarePush didReceiveUnknownNotificationInBackground:(NSDictionary *)notification;

- (void)notificarePush:(NotificarePush *)notificarePush didReceiveUnknownNotificationInForeground:(NSDictionary *)notification;

- (void)notificarePush:(NotificarePush *)notificarePush willOpenNotification:(NotificareNotification *)notification;

- (void)notificarePush:(NotificarePush *)notificarePush didOpenNotification:(NotificareNotification *)notification;

- (void)notificarePush:(NotificarePush *)notificarePush didCloseNotification:(NotificareNotification *)notification;

- (void)notificarePush:(NotificarePush *)notificarePush didFailToOpenNotification:(NotificareNotification *)notification;

- (void)notificarePush:(NotificarePush *)notificarePush didClickURL:(NSURL *)url inNotification:(NotificareNotification *)notification;

- (void)notificarePush:(NotificarePush *)notificarePush willExecuteAction:(NotificareAction *)action;

- (void)notificarePush:(NotificarePush *)notificarePush didExecuteAction:(NotificareAction *)action;

- (void)notificarePush:(NotificarePush *)notificarePush shouldPerformSelectorWithURL:(NSURL *)url inAction:(NotificareAction*)action;

- (void)notificarePush:(NotificarePush *)notificarePush didNotExecuteAction:(NotificareAction *)action;

- (void)notificarePush:(NotificarePush *)notificarePush didFailToExecuteAction:(NotificareAction *)action withError:(NSError *)error;

- (void)notificarePush:(NotificarePush *)notificarePush didChangeNotificationSettings:(BOOL)granted;

@end


@interface NotificarePush : NSObject <NotificareDelegate,NotificareActionsDelegate,UNUserNotificationCenterDelegate>

@property (nonatomic, assign) id<NotificarePushDelegate> notificarePushDelegate;
@property (strong, nonatomic) UNUserNotificationCenter * notificationCenter;
@property (nonatomic,assign) UNAuthorizationOptions authorizationOptions;
@property (nonatomic,assign) UNNotificationPresentationOptions notificationPresentationOptions;
@property (nullable, strong, nonatomic) NSDictionary * launchOptions;
@property (strong, nonatomic) Notificare * notificare;
@property (strong, nonatomic) NotificareActions * notificareActions;

+(NotificarePush*)shared;
-(void)launch;
-(void)registerForNotifications;
-(void)unregisterForNotifications;
-(BOOL)remoteNotificationsEnabled;
-(BOOL)allowedUIEnabled;
-(void)handleOptions:(NSDictionary *)options;
-(void)handleNotification:(NSDictionary*)userInfo completionHandler:(SuccessNotificationBlock)successBlock errorHandler:(ErrorNotificationBlock)errorBlock;
-(void)fetchNotification:(id)notification completionHandler:(SuccessNotificationBlock)successBlock errorHandler:(ErrorNotificationBlock)errorBlock;
-(void)clearPrivateNotification:(NotificareNotification *)notification completionHandler:(SuccessNotificationBlock)successBlock errorHandler:(ErrorNotificationBlock)errorBlock;
-(void)reply:(NotificareNotification *)notification forAction:(NotificareAction *)action andData:(NSDictionary * _Nullable)data completionHandler:(SuccessReplyBlock)successBlock errorHandler:(ErrorReplyBlock)errorBlock;
-(id)notificationController:(NotificareNotification *)notification;
-(void)handleLaunchOptions;
-(void)willPresentNotification:(UNNotification *)notification withCompletionHandler:(void (^)(UNNotificationPresentationOptions))completionHandler;

@end

NS_ASSUME_NONNULL_END
