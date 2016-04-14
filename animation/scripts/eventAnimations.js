var EventAnimations = {};

EventAnimations[CACHE_EVENT.SEARCH] = function(cacheEvent) {
  var architecture = cacheEvent.architecture;
  var cache = architecture.caches[cacheEvent.cacheID];
  var set = cache.sets[cacheEvent.cacheSet];
  var block = set.blocks[cacheEvent.blockId];

  var address = new CacheAddress();
  var addrView = address.getViewForCache(cache);

  var line = false;
  var showingAddress = false;

  this.activate = function(time) {
    switch (time) {
      case 3:
        set.dom.find(".tag-bit").addClass("flash-search");
      case 2:
        if (!line) {
          line = lineToSet(addrView, cache, set);
        }
      case 1:
        if (!showingAddress) {
          $(cache.dom).prepend(addrView);
          showingAddress = true;
        }
      case 0:
        cache.showOpenState();
        break;
    }
  }
  this.deactivate = function(time) {
  }
  this.finish = function() {
    if (line) {
      line.remove();
      line = false;
    }
    if (showingAddress) {
      addrView.remove();
      showingAddress = false;
    }
    set.dom.find(".tag-bit").removeClass("flash-search");
  }
}

EventAnimations[CACHE_EVENT.HIT] = function(cacheEvent) {
  var architecture = cacheEvent.architecture;
  var cache = architecture.caches[cacheEvent.cacheID];
  var set = cache.sets[cacheEvent.cacheSet];
  var block = set.blocks[cacheEvent.blockId];

  this.activate = function(time) {
    console.log(block);
    // 1: show the search
    if (time == 0) {
      block.dom.find(".tag-bit").addClass("flash-hit");
    }
  }

  this.deactivate = function(time) {
  }

  this.finish = function() {
    block.dom.find(".tag-bit").removeClass("flash-hit");
  }
}

function lineToSet(address, cache, set) {
  var idxp = $(address).find(".values .idx").offset();
  var target = set.dom;
  var csp = target.offset();
  var targetY = csp.top + target.height() / 2;
  var targetX = csp.left - 20;
  return new drawArrow(
      {
        x:idxp.left, 
        y:idxp.top + 20
      }, 
      {
        x:targetX,
        y:targetY
      },
      [
        {
          x:idxp.left,
          y:targetY
        }
      ]
  );

}

