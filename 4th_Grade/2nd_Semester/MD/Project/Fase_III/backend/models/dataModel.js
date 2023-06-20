const { firebaseConfig } = require('../config/firebaseConfig');
const { initializeApp } = require("firebase/app");
const {getDatabase, ref, set, child, push, update, get, limitToLast, orderByChild, query, onValue, once} = require("firebase/database");

// Initialize Firebase
const appFirebase = initializeApp(firebaseConfig);
const database = getDatabase(appFirebase);

module.exports = {
    database,
    ref,
    set,
    child,
    push,
    update,
    get,
    query,
    orderByChild,
    limitToLast,
    onValue,
    once
};