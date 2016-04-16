var arrowID = 0;
function drawArrow(from, to, stops, target) {

  if (arguments.length == 2) {
    stops = [];
  }

  var ns = 'http://www.w3.org/2000/svg';
  var svg = document.createElementNS(ns, 'svg');

  var w = from.x < to.x ? to.x - from.x : from.x - to.x;
  var h = from.y < to.y ? to.y - from.y : from.y - to.y;
  // todo: support stops that are outside of from/to ranges
  h += 10;
  svg.setAttribute("width",w);
  svg.setAttribute("height",h);
  svg.setAttribute("class","arrow");

  var l = from.x < to.x ? from.x : to.x;
  var t = from.y < to.y ? from.y : to.y; 
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

  var pfx,pty,ptx,pty;
  pfx = from.x < to.x ? 2 : w;
  pfy = from.y < to.y ? 2 : h;
  ptx = to.x < from.x ? 6 : w - 6;
  pty = to.y < from.y ? 6 : h - 6;
  if (from.x == to.x) pfx = ptx = 5;
  if (from.y == to.y) pfy = pty = 5;
  var pathString = "M " + pfx + "," + pfy;
  for (var i = 0; i < stops.length; i++) {
    var stx, sty;
    // todo: support stops outside of to/from range
    sty =  stops[i].y - t;
    stx =  stops[i].x - l;
    stx += 2;
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
