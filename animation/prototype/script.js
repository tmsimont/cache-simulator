$(document).ready(function() {

  var sizingAdjustments = [];

  function addressView(model) {
    var dom = $("<div>");
    dom.addClass("address");
  
    var labels = $("<div>");
    labels.addClass("labels");
    dom.append(labels);
  
    var values = $("<div>");
    values.addClass("values");
    dom.append(values);
    
    // tag
    var lblTag = $("<div>");
    lblTag.addClass("tag");
    lblTag.text("Tag");
    labels.append(lblTag);
    var valTag = $("<div>");
    valTag.addClass("tag");
    valTag.text("010110101");
    values.append(valTag);

    // index
    var lblIdx = $("<div>");
    lblIdx.addClass("idx");
    lblIdx.text("Index");
    labels.append(lblIdx);
    var valIdx = $("<div>");
    valIdx.addClass("idx");
    valIdx.text("10");
    values.append(valIdx);

    // offset
    var lblOffset = $("<div>");
    lblOffset.addClass("offset");
    lblOffset.text("Offset");
    labels.append(lblOffset);
    var valOffset = $("<div>");
    valOffset.addClass("offset");
    valOffset.text("0110");
    values.append(valOffset);

    return dom;

  }


  function cacheView(model) {
    var dom = $("<div>");
    dom.addClass("cache");

    for (var i=0; i < model.lines; i++) {
      var set = $("<div>");
      set.addClass("cache-line");

      var valid = $("<div>");
      valid.addClass("bit-group");
      valid.addClass("valid-bits");
      for (var k=0; k < model.validBits; k++) {
        var bit = $("<div>");
        bit.addClass("cache-bit");
        bit.addClass("valid-bit");
        valid.append(bit);
      }
      set.append(valid);

      var tag = $("<div>");
      tag.addClass("bit-group");
      tag.addClass("tag-bits");
      for (var k=0; k < model.tagBits; k++) {
        var bit = $("<div>");
        bit.addClass("cache-bit");
        bit.addClass("tag-bit");
        tag.append(bit);
      }
      set.append(tag);

      var data = $("<div>");
      data.addClass("bit-group");
      data.addClass("data-bits");
      for (var k=0; k < model.dataBits; k++) {
        var bit = $("<div>");
        bit.addClass("cache-bit");
        bit.addClass("data-bit");
        data.append(bit);
      }
      set.append(data);

      dom.append(set);
    }
    
    sizingAdjustments.push(function() {
      var width = 0;
      width += dom.find(".valid-bits").outerWidth(true);
      width += dom.find(".tag-bits").outerWidth(true);
      width += dom.find(".data-bits").outerWidth(true);
      $(dom).width(width);
    });

    return dom;
  }

  function nwaySetAssociative(model) {
    var dom = $("<div>");
    dom.addClass("associative-set");
    for (var i = 0; i < model.sets; i++) {
      var row = $("<div>");
      row.addClass("cache-set-container");
      var cache = cacheView(model.perCache);
      row.append(cache);
      dom.append(row);
    }
    
    return dom;
  }


  var arrowID = 0;
  function drawArrow(from, to, stops) {
    var target = "stage";

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

    document.getElementById(target).appendChild(svg);


  }

  $("#stage").append(addressView({}));


  var model = {
    sets: 2,
    perCache: {
      lines: 20,
      validBits: 1,
      tagBits: 12,
      dataBits: 29
    }
  }
  $("#stage").append(nwaySetAssociative(model));


  for (var i = 0; i < sizingAdjustments.length; i++) {
    sizingAdjustments[i]();
  }

  $(".associative-set").css("left", "+=150");
  $(".associative-set").css("top", "+=20");

  var idxp = $(".address .values .idx").offset();
  idxp.left
  idxp.top

  
  $(".cache-line").hover(function() {
  }, function() {
  });
  



  $(".associative-set .cache-set-container").each(function() {
    var csp = $(this).offset();
    var targetY = csp.top + $(this).outerHeight() / 2;
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
  });

  
});
