#import "render_impl.h"

@implementation Metal_IMPL

- (instancetype) init_with_swap_chain : (CAMetalLayer*) swap_chain {
	self = [super init];
    if (self) {
    	self.swap_chain = swap_chain;
    	self.gpu = self.swap_chain.device;
    	self.queue = [self.gpu newCommandQueue];
    }
    return self;
}

- (void) clear {
	MTLClearColor color = MTLClearColorMake(1, 0, 0, 1);
	id<CAMetalDrawable> surface = [self.swap_chain nextDrawable];
    MTLRenderPassDescriptor *pass = [MTLRenderPassDescriptor renderPassDescriptor];
    pass.colorAttachments[0].clearColor = color;
    pass.colorAttachments[0].loadAction  = MTLLoadActionClear;
    pass.colorAttachments[0].storeAction = MTLStoreActionStore;
    pass.colorAttachments[0].texture = surface.texture;
    id<MTLCommandBuffer> buffer = [self.queue commandBuffer];
    id<MTLRenderCommandEncoder> encoder = [buffer renderCommandEncoderWithDescriptor:pass];
    [encoder endEncoding];
    [buffer presentDrawable:surface];
    [buffer commit];
}

@end