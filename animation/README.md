## Cache Animation

You must have a simple web server running in order to view these files. The index.html file calls a file with AJAX, so you can't view it on your file system (with a file:///C:/  protocol)

We were unable to fully integrate the animator with our simulator code, so right now the only thing you can really do is play with the animation that we demonstrated in class. The best place to do this is on [the live demo](http://www.trevorsimonton.com/r/cache-animation/index.html).

If you'd prefer to run the files locally, there are [myriad ways to host static HTML files locally](https://gist.github.com/willurd/5720255).

### Structure

`/trace` 

This folder contains the JSON script used to drive the animation.

`/css`

This folder contains CSS styles, which are compiled from `/css/styles.scss` with [SCSS](https://teamtreehouse.com/community/what-is-the-difference-between-a-file-css-and-a-scss)

`/libs`

This folder contains 3rd party libraries

`/scripts`

This is where all of the JavaScript that drives the application resides.

### EventTimeline 

The core driver in the JavaScript layer is in `eventTimeline.js`

This file contains code that activates events on a timeline. Each event has a start and end point in time. At every "click" in between the start and end, there is a call to the animation instance's "activate" function.

See `eventAnimations.js` for a list of animation objects that are configured to show different states at each click of activation.

The `time` value passed to `activate()` is relative to the animation instance. So, if the animation starts at time 123123 and ends at 123133, then time will be called at 0,1,2,3,4,5,6,7,8 and 9 as time passes over this animation.

At each point in this relative timeline, the `activate()` and `deactivate()` functions should control the state of the view.
