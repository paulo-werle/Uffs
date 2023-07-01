import { readFile } from 'fs/promises';

import Terminal from './src/Terminal.js';
import EventBus from './src/EventBus.js';
import Router from './src/Router.js';
import Dht from './src/Dht.js';

const configFileName = './assets/config.json';
const routerId = process.argv[2];

const getConnections = async (configFileName) => JSON.parse(
  await readFile(
    new URL(configFileName, import.meta.url)
  )
);

const findConnection = (connection) => (
  connection.id == routerId
);

getConnections(configFileName).then(
  (connections) => {
    const eventBus = new EventBus(
      routerId,
      connections
    );

    const dht = new Dht(
      routerId,
      connections,
      connections.find(findConnection),
      eventBus
    );

    new Terminal(
      eventBus,
      dht
    );

    new Router(
      connections.find(findConnection),
      eventBus,
      dht
    );
  }
);

