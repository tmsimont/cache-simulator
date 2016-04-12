$(document).ready(function() {

  // read params
  var params = new CacheParameters();

  // set up simulated cache architecture
  var ca = new CacheArchitecture();
  ca.addCache(params);
  //ca.addCache(params);
  $("#stage").append(ca.dom);
  ca.adjustSizing();


  // events timeline
  var events = [];

  // event: cache search
  events.push(new CacheEvent(ca, {
    title : "L1 hit",
    start : 0,
    end : 10,
    type : CACHE_EVENT_HIT,
    address : "10100101011011101011010101",
    cacheID: 0,
    cacheSet : 0,
    blockId : 2
  }));

  // queue animation timeline...
  events[0].animate();

  console.log(events);

  var timeline = new EventTimeline($("#timeline"));

});
