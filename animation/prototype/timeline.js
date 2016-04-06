$(document).ready(function() {

  // use number type where number will be the nanosecond clock
  // see: http://visjs.org/docs/data/dataset.html
  var items = new vis.DataSet({
    type: { start: 'Number', end: 'Number' }
  });

  // add items to the DataSet
  items.add([
    {id: 1, content: 'item 1', start: 1, end : 9},
    {id: 2, content: 'item 2', start: 10, end : 19},
    {id: 3, content: 'item 3', start: 20, end: 29},
    {id: 4, content: 'item 4', start: 30, end: 50},
    {id: 5, content: 'item 5', start: 51, end: 69},
    {id: 6, content: 'item 6', start: 70}
  ]);

  var container = document.getElementById('timeline');
  // see http://visjs.org/docs/timeline/
  var options = {
    format: '',
    start: 1,
    end: 100,
    showCurrentTime: false
  };

  var timeline = new vis.Timeline(container, items, options);

  // example API calls
  document.getElementById('window1').onclick = function() {
    timeline.setWindow('2014-01-01', '2014-04-01');
  };
  document.getElementById('window2').onclick = function() {
    timeline.setWindow('2014-01-01', '2014-04-01', {animation: false});
  };
  document.getElementById('fit').onclick = function() {
    timeline.fit();
  };
  document.getElementById('select').onclick = function() {
    timeline.setSelection([5, 6], {
      focus: true
    });
  };
  document.getElementById('focus1').onclick = function() {
    timeline.focus(2);
  };
  document.getElementById('focus2').onclick = function() {
    timeline.focus([5, 6], {animation: {duration: 3000, easingFunction: 'linear'}}); // ms
  };
  document.getElementById('focus3').onclick = function() {
    var selection = timeline.getSelection();
    timeline.focus(selection);
  };
  document.getElementById('moveTo').onclick = function() {
    timeline.moveTo('2014-02-01');
  };

});
