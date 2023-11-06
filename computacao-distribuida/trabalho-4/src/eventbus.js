import { EventEmitter  } from 'node:events';

class EventBus extends EventEmitter {

  constructor(id, connections) {
    super();
    this.id = id;
    this.connections = connections;
  }

  remote(to) {
    return this.connections.find(current => Number(current.id) === Number(to));
  }
}

export default EventBus;