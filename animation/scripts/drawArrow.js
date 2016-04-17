var arrowID = 0;
function drawArrow(from, to, stops, target) {

  if (arguments.length == 2) {
    stops = [];
  }

  var ns = 'http://www.w3.org/2000/svg';
  var svg = document.createElementNS(ns, 'svg');


  // support stops that are outside of from/to ranges
  var minstopX = from.x < to.x ? from.x : to.x;
  var minstopY = from.y < to.y ? from.y : to.y;
  var maxstopX = from.x > to.x ? from.x : to.x;
  var maxstopY = from.y > to.y ? from.y : to.y;
  for (var i = 0; i < stops.length; i++) {
    if (stops[i].x < minstopX) minstopX = stops[i].x; 
    if (stops[i].y < minstopY) minstopY = stops[i].y; 
    if (stops[i].x > maxstopX) maxstopX = stops[i].x; 
    if (stops[i].y > maxstopY) maxstopY = stops[i].y; 
  }
  var w = maxstopX - minstopX;
  var h = maxstopY - minstopY;
  w += 15;
  h += 15;

  svg.setAttribute("width",w);
  svg.setAttribute("height",h);
  svg.setAttribute("class","arrow");

  var l = minstopX;
  var t = minstopY; 
  svg.setAttribute("style", "left:"+l+"px;top:"+t+"px;");

  var defs = document.createElementNS(ns, "defs");
  var marker = document.createElementNS(ns, "marker");
  var id = "arrow-" + arrowID++;
  marker.setAttribute("id", id);
  marker.setAttribute("markerWidth", 4);
  marker.setAttribute("markerHeight", 10);
  marker.setAttribute("markerUnits", "strokeWidth");
  marker.setAttribute("refX", 1);
  marker.setAttribute("refY", 5);
  marker.setAttribute("viewBox", "0 0 10 10");
  marker.setAttribute("orient", "auto");

  var path = document.createElementNS(ns, "path");
  path.setAttribute("d","M 0 0 L 10 5 L 0 10 z");
  path.setAttribute("fill","context-stroke");

  marker.appendChild(path);
  defs.appendChild(marker);
  svg.appendChild(defs);

  var instance = document.createElementNS(ns, "path");

  var pfx = from.x - l + 6;
  var ptx = to.x - l + 6;
  var pfy = from.y - t + 6;
  var pty = to.y - t + 6;
  if (pfx == ptx) pfx = ptx = 6;
  if (pfy == pty) pfy = pty = 6;
  var pathString = "M " + pfx + "," + pfy;
  for (var i = 0; i < stops.length; i++) {
    var stx, sty;
    // todo: support stops outside of to/from range
    sty =  stops[i].y - t;
    stx =  stops[i].x - l;
    stx += 6;
    sty += 6;
    pathString +=         " L " + stx + "," + sty;
  }
  pathString +=           " L " + ptx + "," + pty;

  instance.setAttribute("d", pathString);
  instance.setAttribute("stroke-width", "2");
  instance.setAttribute("stroke", "black");
  instance.setAttribute("fill", "none");
  instance.setAttribute("marker-end", "url(#"+id+")");

  svg.appendChild(instance);

  $(target).append(svg);

  this.remove = function() {
    svg.remove();
  }

}
