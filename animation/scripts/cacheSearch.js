function CacheSearch() {
}
function lineToSet(cache, setIdx) {
  var idxp = $(".address .values .idx").offset();
  var target = cache.sets[setIdx].dom;
  console.log(target);
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

