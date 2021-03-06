var CACHE_EVENT = {
  SEARCH       : 0,
  HIT          : 1,
  HIT_VALID    : 2,
  HIT_INVALID  : 3,
  MISS         : 4,
  REPLACE      : 5
}

function CacheEvent(params) {
  var self = this;
  for (var i in params) {
    self[i] = params[i];
  }
  if (params['instruction']) {
    self.windowTitle = "Current instruction: " + params['instruction'];
  }

  if (typeof params.animator == "undefined")
    self.animator = new EventAnimations[self.type](this);

  if (typeof params.activate == "undefined")
    self.activate = function(time) {
      self.animator.activate(time);
    }

  if (typeof params.deactivate == "undefined")
    self.deactivate = function(time) {
      self.animator.deactivate(time);
    }

  if (typeof params.finish == "undefined")
    self.finish = function() {
      self.animator.finish();
    }
}

