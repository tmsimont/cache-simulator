$(document).ready(function() {

  // read params
  var params = new CacheParameters();

  // set up simulated cache architecture
  var ca = new CacheArchitecture();
  ca.addCache(params);
  ca.addCache(params);
  $("#stage").append(ca.dom);
  ca.adjustSizing();


  // events timeline
  var events = [];

  // event: cache search
  events.push(new CacheEvent(ca, {
    title : "L1 hit",
    start : 0,
    end : 9,
    type : CACHE_EVENT_HIT,
    address : "10100101011011101011010101",
    cacheID: 0,
    cacheSet : 0,
    blockId : 2
  }));
  events.push(new CacheEvent(ca, {
    title : "L1 hit",
    start : 9,
    end : 19,
    type : CACHE_EVENT_HIT,
    address : "10100101011011101011010101",
    cacheID: 1,
    cacheSet : 1,
    blockId : 3
  }));
  events.push(new CacheEvent(ca, {
    title : "L1 hit",
    start : 19,
    end : 29,
    type : CACHE_EVENT_HIT,
    address : "10100101011011101011010101",
    cacheID: 1,
    cacheSet : 1,
    blockId : 1
  }));

  // queue animation timeline...
  var timeline = new EventTimeline($("#timeline"));
  for (var i = 0; i < events.length; i++) {
    timeline.addEvent(events[i]);
  }

  // initialize timeline
  timeline.init();

  

});
