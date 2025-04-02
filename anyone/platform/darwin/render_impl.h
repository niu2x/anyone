#import <Foundation/Foundation.h>
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>

@interface Metal_IMPL : NSObject

@property (nonatomic, weak) CAMetalLayer *swap_chain;
@property (nonatomic, strong) id<MTLDevice> gpu;
@property (nonatomic, strong) id<MTLCommandQueue> queue;
@property (nonatomic) MTLClearColor clear_color;

- (instancetype) init_with_swap_chain: (CAMetalLayer*) swap_chain;
- (void) clear;


@end