#!/usr/bin/env python3

from pymongo import MongoClient
from multipledispatch import dispatch 

class Database(object):
    def __init__(self, *args, **kwargs):
        self.mongo = "mongo"
        self.port = '27017'

        self.client = None
        self.db = None

    def connect(self):
        self.client = MongoClient(self.mongo, self.port)

    def connectToDatabase(self, dbName):
        self.db = self.client['{}'.format(dbName)]

    @dispatch(object, str)
    def connectToCollection(self, collection):
        self.db['{}'.format(collection)]

    @dispatch(object, str, str)
    def connectToCollection(self, dbName, collection):
        self.connectToDatabase(dbName)
        self.connectToCollection(collection)
