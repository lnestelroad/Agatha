db.createUser({
  user: 'liam',
  pwd: 'raspberry',
  roles: [{role: 'readWrite', db: 'kitchen'}]
})