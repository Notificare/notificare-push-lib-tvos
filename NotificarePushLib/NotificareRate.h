//
//  Rate.h
//  NotificarePushLib
//
//  Created by Joel Oliveira on 1/24/13.
//  Copyright (c) 2013 Notificare. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>
#import "NotificareNotification.h"
#import "NotificationType.h"
#import "NotificationDelegate.h"
#import "NotificareActions.h"
#import "NSString+FromBundle.h"
#import "UIImage+FromBundle.h"

NS_ASSUME_NONNULL_BEGIN

@interface NotificareRate : NSObject <NotificationType>

@property (nonatomic, strong) id<NotificationDelegate> delegate;
@property (nonatomic, strong) NotificareNotification * notification;
@property (nonatomic, strong) NotificareActions * notificareActions;
@property (strong, nonatomic) UIAlertController * alert;

-(id)handleNotification;

@end
NS_ASSUME_NONNULL_END
