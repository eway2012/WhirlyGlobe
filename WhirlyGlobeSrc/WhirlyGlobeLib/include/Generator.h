/*
 *  DrawGenerator.h
 *  WhirlyGlobeLib
 *
 *  Created by Steve Gifford on 10/10/11.
 *  Copyright 2011 mousebird consulting. All rights reserved.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

#import <UIKit/UIKit.h>
#import <map>
#import <list>
#import "Texture.h"
#import "Drawable.h" 
#import "GlobeView.h"

/// @cond
@class WhirlyKitRendererFrameInfo;
/// @endcond

namespace WhirlyKit
{
    
/** The Generator is a base class for objects that want to produce
    Drawables every frame.  This is for things like particle systems
    or layers that want custom animation.
  */
class Generator : public Identifiable
{
public:
    Generator() { }
    Generator(const std::string &inName) : name(inName) { }
    virtual ~Generator() { }

    /// Generate drawables in one of two lists for the renderer.
    /// World drawables are drawn in 3D, screen drawables are drawn in 2D, after the 3D.
    /// The renderer deletes the drawables at the end of the frame
    virtual void generateDrawables(WhirlyKitRendererFrameInfo *frameInfo,
                                   std::vector<Drawable *> &worldDrawables,std::vector<Drawable *> &screenDrawables) { };
    
    /// An optional name used to identify the generator
    std::string name;
};

/** The Generator Change Request is the base class for communication
    with a specific generator.  You override this with your own specific
    request and it'll be delivered to the generate your request.
  */
class GeneratorChangeRequest : public ChangeRequest
{
public:
    /// Construct with the target generator ID.
    GeneratorChangeRequest(SimpleIdentity genId) : genId(genId) { }
    GeneratorChangeRequest() { }

    /// Run the generator request.  Don't override this one
    void execute(Scene *scene,WhirlyKitView *view);

    /// Override this method to do whatever you want to do to the generator
    virtual void execute2(Scene *scene,Generator *drawGen) = 0;
    
protected:
    /// Generator that we're going to modify
    SimpleIdentity genId;
};
    

}
