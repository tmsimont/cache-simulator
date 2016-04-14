$(document).ready(function() {

  // set up simulated cache architecture
  var ca = new CacheArchitecture();
  
  // todo: parse real params
  var paramsL1 = new CacheParameters();
  ca.addCache(paramsL1);
  var paramsL2 = new CacheParameters();
  paramsL2.name = "L2";
  paramsL2.size = 512;
  paramsL2.associativity = 4;
  paramsL2.missPenalty = 100;
  paramsL2.hitTime = 2;
  ca.addCache(paramsL2);

  $("#stage").append(ca.dom);

  ca.init();

  //ca.adjustSizing();


  // events timeline
  var events = [];

  // event: cache search
  events.push(new CacheEvent({
    architecture : ca,
    title : "L1 search",
    start : 0,
    end : 9,
    type : CACHE_EVENT.SEARCH,
    address : "10100101011011101011010101",
    cacheID: 0,
    cacheSet : 0,
    blockId : 2
  }));
  events.push(new CacheEvent({
    architecture : ca,
    title : "L1 hit",
    start : 10,
    end : 19,
    type : CACHE_EVENT.HIT,
    address : "10100101011011101011010101",
    cacheID: 0,
    cacheSet : 0,
    blockId : 2
  }));
  events.push(new CacheEvent({
    architecture : ca,
    title : "L1 hit",
    start : 20,
    end : 29,
    type : CACHE_EVENT.HIT,
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
  timeline.init(function() {
    setTimeout(function() {
      $("#stage-container").height(
        .95 * $("#main").height() - $("#timeline").outerHeight() 
      );
    }, 100);
  });

  

});
