var CACHE_EVENT_HIT  = 0;
var CACHE_EVENT_MISS = 1;

function CacheEvent(ca, params) {
  this.ca = ca;
  this.params = params;
  var animator = new EventAnimations[params.type](this);
  this.animate = function(time, E) {
    animator.animate(time, E);
  }
  this.finish = function(E) {
    animator.finish(E);
  }
}

var EventAnimations = {};
EventAnimations[CACHE_EVENT_HIT] = function(cacheEvent) {
  var address = new CacheAddress();
  var addrView = addressView(address);

  this.animate = function(time, E) {
    // 1: show the search
    if (time == 0) {
      // new event, address to read...
      $("#stage").prepend(addrView);

      CacheSearch({
        address : address,
        cache   : cacheEvent.ca.caches[cacheEvent.params.cacheID],
        set     : cacheEvent.ca.caches[cacheEvent.params.cacheID]
                   .sets[cacheEvent.params.cacheSet],
        block   : cacheEvent.ca.caches[cacheEvent.params.cacheID]
                   .sets[cacheEvent.params.cacheSet]
                   .blocks[cacheEvent.params.blockId]
      });
    }

    // 2: show the hit
    // todo
  }

  this.finish = function(E) {
    addrView.remove();
    // todo: clean specific arrow
    $("#stage svg").remove();
    $(".flash-hit").removeClass("flash-hit");
  }
}
