class Dht {

  constructor(id, connections, config, eventBus) {
    this.id = Number(id);
    this.config = config;
    this.eventBus = eventBus;
    this.connections = connections;

    this.memory = {};
    this.hashNumber = 0;
    this.routerTable = {};

    this.#instanceMemory();
    this.#defineHashNumber();
    this.#instanceRouterTable();
  }

  #instanceMemory() {
    for (var index = 0; index < this.config.allocation; index++) {
      this.memory[index] = '';
    }
  }

  #defineHashNumber() {
    this.connections.forEach( (connection) => {
      this.hashNumber += connection.allocation;
    });
  }

  #instanceRouterTable() {
    this.connections.forEach( (connection, index) => {
      let tableInit = connection.table[0];
      let tableEnd = connection.table[1];
      let routerMemories = [];

      for (var indey = tableInit; indey <= tableEnd; indey++) {
        routerMemories.push(indey);
      }

      this.routerTable[connection.id] = routerMemories;
    })
  }

  hash(rg, position) {
    if (position !== null) {
      return position % this.hashNumber
    }

    return rg % this.hashNumber
  }

  address(hash) {
    return hash % this.config.allocation;
  }

  router(hash) {
    const id = Object.keys(this.routerTable).find((key) => (
      this.routerTable[key].includes(Number(hash))
    ))

    return Number(id)
  }

  busyMemory(address) {
    return this.memory[address] !== ''
  }

  handleOperation(message) {
    if ( message.op == 'insert') {
      console.log(message.hash)
      this.insert(message.data, message.hash);
    }
    else if ( message.op == 'search' ) {
      this.eventBus.emit('sendToAnotherRouter',{ to: message.from, op: 'answer', data: this.search(message.data, message.hash)});
    }
    else if( message.op == 'answer') {
      console.log(message.data);
    }
  }

  insert(item, position = null) {
    let rg = item.rg
    let hash = this.hash(rg, position)

    let router = this.router(hash);
    if (router !== this.id) {
      return this.eventBus.emit('sendToAnotherRouter', { to: router, op: 'insert', hash: hash, data: item });
    }

    let address = this.address(hash)
    if (this.busyMemory(address)){
      return this.insert(item, hash + 1);
    }

    this.memory[address] = item
  }

  search(rg, position = null) {
    let hash = this.hash(rg, position);

    let router = this.router(hash);
    if (router !== this.id) {
      return this.eventBus.emit('sendToAnotherRouter', { from: this.id, to: router, op: 'search', hash: hash, data: rg });
    }

    let address = this.address(hash)
    if (this.memory[address].rg === rg) {
      return this.memory[address];
    }

    return this.search(rg, hash + 1);
  }
}

export default Dht;