$(document).ready(function() {
  var params = new CacheParameters();
  var ca = new CacheArchitecture();
  ca.addCache(params);
  //ca.addCache(params);
  $("#stage").append(ca.dom);
  ca.adjustSizing();


  // new event, address to read...
  var addr = new CacheAddress();
  var addrView = addressView(addr);
  $("#stage").prepend(addrView);
  
  lineToSet(ca.caches[0], 0)

});
