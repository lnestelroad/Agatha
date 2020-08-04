#!/usr/bin/env python3

import os
import random
import string
import cherrypy
import requests
from pymongo import MongoClient
from jinja2 import Environment, FileSystemLoader

from mongo_database import Database

env = Environment(loader=FileSystemLoader('templates'))


class Agatha(object):
    @cherrypy.expose
    def index(self, submit=""):
        tmpl = env.get_template('jinjaTest.html')

        return tmpl.render()

    @cherrypy.expose
    def kitchen(self, *args, **kwargs):
        tmpl = env.get_template('kitchen.html')
        fname = kwargs.get('fname', None) if kwargs.get('fname', None) else ''
        lname = kwargs.get('lname', None) if kwargs.get('lname', None) else ''

        return tmpl.render(firstname=fname, lastname=lname)

    @cherrypy.expose
    def camera(self, fname='', lname=''):
        tmpl = env.get_template('camera.html')
        return tmpl.render(firstname=fname, lastname=lname)

    @cherrypy.expose
    def author(self):
        tmpl = env.get_template('author.html')
        return tmpl.render()


@cherrypy.expose
class Agatha_API(object):

    @cherrypy.tools.accept(media='application/json')
    @cherrypy.tools.json_out()
    def GET(self):
        return {"nice": "Nice"}

    @cherrypy.tools.json_in()
    def POST(self, length=8):
        print(cherrypy.request.json)
        some_string = ''.join(random.sample(string.hexdigits, int(length)))
        cherrypy.session['mystring'] = some_string
        return some_string

    def PUT(self, another_string):
        cherrypy.session['mystring'] = another_string

    def DELETE(self):
        cherrypy.session.pop('mystring', None)


if __name__ == "__main__":
    conf = {
        'global': {
            'server.socket_host': '0.0.0.0',
            'server.socket_port': 8080
        },
        # '/favicon.ico': {
        #         'tools.staticfile.on': True,
        #         'tools.staticfile.filename': './public/images/favicon_io/favicon.ico'
        # },
        '/': {
            'tools.sessions.on': True,
            'tools.staticdir.root': os.path.abspath(os.getcwd())
        },
        '/generator': {
            'request.dispatch': cherrypy.dispatch.MethodDispatcher(),
            'tools.response_headers.on': True,
            'tools.response_headers.headers': [('Content-Type', 'application/json')],
        },
        '/static': {
            'tools.staticdir.on': True,
            'tools.staticdir.dir': './public'
        }
    }
    webapp = Agatha()
    webapp.generator = Agatha_API()
    cherrypy.quickstart(webapp, '/', conf)
