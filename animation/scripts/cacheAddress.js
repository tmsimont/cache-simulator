function CacheAddress(cache, bits) {
  this.bits = bits;

  var address = this;
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
  var tagBits = cache.getTagBits(bits);
  var tagString = "";
  for (var i = 0; i < tagBits.length; i++) {
    tagString = tagString + tagBits[i];
  }
  valTag.text(tagString);
  values.append(valTag);

  // index
  var lblIdx = $("<div>");
  lblIdx.addClass("idx");
  lblIdx.text("Index");
  labels.append(lblIdx);
  var valIdx = $("<div>");
  valIdx.addClass("idx");
  var idxBits = cache.getIndexBits(bits);
  var idxString = "";
  for (var i = 0; i < idxBits.length; i++) {
    idxString = idxString + idxBits[i];
  }
  valIdx.text(idxString);
  values.append(valIdx);

  // offset
  var lblOffset = $("<div>");
  lblOffset.addClass("offset");
  lblOffset.text("Offset");
  labels.append(lblOffset);
  var valOffset = $("<div>");
  valOffset.addClass("offset");
  var offsetBits = cache.getOffsetBits(bits);
  var offsetString = "";
  for (var i = 0; i < offsetBits.length; i++) {
    offsetString = offsetString + offsetBits[i];
  }
  valOffset.text(offsetString);
  values.append(valOffset);
  
  this.dom = dom;


}
