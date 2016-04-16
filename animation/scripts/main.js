$(document).ready(function() {

  // set up simulated cache architecture
  var ca = new CacheArchitecture();
  
  // todo: parse real params
  var paramsL1 = new CacheParameters();
  ca.addCache(paramsL1);
  var paramsL2 = new CacheParameters();
  paramsL2.name = "L2";
  paramsL2.size = 512 * 8;
  paramsL2.associativity = 4;
  paramsL2.missPenalty = 100;
  paramsL2.hitTime = 2;
  ca.addCache(paramsL2);

  $("#stage").append(ca.dom);
  ca.init();

  // events timeline
  $.ajax({
    url: "trace/reads.json",
    dataType: "json",
    success: function(data) {

      // parse JSON to CacheEvent instances
      var events = [];
      for (var i in data) {
        data[i].architecture = ca;
        events.push(new CacheEvent(data[i]));
      }

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
    },
    error : function() {
      console.log(arguments);
    }
  });

});
