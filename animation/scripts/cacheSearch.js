function CacheSearch(params) {

  // params: {
  //   address : (CacheAddress),
  //   cache   : (Cache),
  //   set     : (CacheSet),
  //   block   : (CacheBlock or FALSE)
  // }

  // step 1: identify set from address
  lineToSet(params.cache, params.set);

  // step 2: compare tags
  setTimeout(function() {
    compareTags(params.set, params.block);
  }, 500);

  // todo: valid bit miss?
  

  return {
    
  }
}

function lineToSet(cache, set) {
  var idxp = $(".address .values .idx").offset();
  var target = set.dom;
  var csp = target.offset();
  var targetY = csp.top + target.height() / 2;
  var targetX = csp.left - 20;
  drawArrow(
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

function compareTags(set, block) {
  setTimeout(function() {
    set.dom.find(".tag-bit").addClass("flash-search");
    if (block) {
      block.dom.find(".tag-bit").addClass("flash-hit");
    }
  }, 100);
  setTimeout(function() {
    set.dom.find(".tag-bit").removeClass("flash-search");
  }, 500);
}

function flashValid(block) {
}
