#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Address {
  int id;
  int set;
  char *name;
  char *email;
} Address;

typedef struct Database {
  size_t max_data;
  size_t max_rows;
  Address *rows;
} Database;

typedef struct Connection {
  FILE *file;
  Database *db;
} Connection;

void die(const char *message, Connection *conn) {
  if (errno) {
    perror(message);
  } else {
    printf("Error: %s\n", message);
  }

  if (conn) {
    fclose(conn->file);
    if (conn->db)
      free(conn->db);
    free(conn);
  };

  exit(1);
}

void Address_print(Address *addr) {
  printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(Connection *conn) {
  int rc = fread(conn->db, sizeof(Database), 1, conn->file);
  if (rc != 1)
    die("Failed to load database.", conn);
}

Connection *Database_open(const char *filename, char mode) {
  Connection *conn = malloc(sizeof(Connection));
  if (!conn)
    die("Memory error", conn);

  conn->db = malloc(sizeof(Database));
  if (!conn->db)
    die("Memory error.", conn);

  if (mode == 'c') {
    conn->file = fopen(filename, "w");
  } else {
    conn->file = fopen(filename, "r+");

    if (conn->file) {
      Database_load(conn);
    }
  }
  if (!conn->file)
    die("Failed to open the file.", conn);
  return conn;
}

void Database_close(Connection *conn) {
  if (conn) {
    if (conn->file)
      fclose(conn->file);
    if (conn->db) {
      free(conn->db);
    }
    free(conn);
  }
}

void Database_write(Connection *conn) {
  rewind(conn->file);
  int rc = fwrite(conn->db, sizeof(Database), 1, conn->file);
  if (rc != 1)
    die("Failed to write database", conn);

  rc = fflush(conn->file);
  if (rc == -1)
    die("Cannot flush database.", conn);
}

void Database_create(Connection *conn) {
  printf("Enter max rows: ");
  size_t max_rows;
  scanf("%zu", &max_rows);

  printf("Enter max data: ");
  size_t max_data;
  scanf("%zu", &max_data);

  conn->db->max_rows = max_rows;
  conn->db->max_data = max_data;

  Address *rows = (Address *)malloc(sizeof(Address) * conn->db->max_rows);
  if (!rows)
    die("Unable to create database", conn);
  conn->db->rows = rows;

  for (size_t i = 0; i < max_rows; i++) {
    char *name = (char *)malloc(conn->db->max_data);
    char *email = (char *)malloc(conn->db->max_data);

    memset(name, 0, conn->db->max_data);
    memset(email, 0, conn->db->max_data);

    Address addr = {.id = i, .set = 0, .name = name, .email = email};
    conn->db->rows[i] = addr;
  }
}

void Database_set(Connection *conn, int id, char *name, char *email) {
  Address *addr = &conn->db->rows[id];
  if (addr->set)
    die("Already set, delete it first", conn);

  addr->set = 1;

  name[conn->db->max_data - 1] = '\0';
  email[conn->db->max_data - 1] = '\0';

  strncpy(addr->name, name, conn->db->max_data);

  strncpy(addr->email, email, conn->db->max_data);
}

void Database_get(Connection *conn, int id) {
  Address *addr = &conn->db->rows[id];
  if (addr->set) {
    Address_print(addr);
  } else {
    die("ID is not set.", conn);
  }
}

void Database_delete(Connection *conn, int id) {
  Address addr = {.id = id, .set = 0};
  conn->db->rows[id] = addr;
}

void Database_list(Connection *conn) {
  int i = 0;
  Database *db = conn->db;

  for (i = 0; i < conn->db->max_rows; i++) {
    Address *cur = &db->rows[i];
    if (cur->set == 1) {
      Address_print(cur);
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc < 3)
    die("USAGE: ex17 <dbfile> <action> [action params]", NULL);
  char *filename = argv[1];
  char action = argv[2][0];
  Connection *conn = Database_open(filename, action);

  int id = 0;
  if (argc > 3) {
    id = atoi(argv[3]);
    if (id >= conn->db->max_rows) {
      die("There's not that many records.", conn);
    }
  }
  switch (action) {
  case 'c':
    Database_create(conn);
    Database_write(conn);
    break;
  case 'g':
    if (argc != 4)
      die("Need an id to get", conn);
    Database_get(conn, id);
    break;
  case 's':
    if (argc != 6)
      die("Need id, name, email to set", conn);
    Database_set(conn, id, argv[4], argv[5]);
    Database_write(conn);
    break;
  case 'd':
    if (argc != 4)
      die("Need id to delete", conn);
    Database_delete(conn, id);
    Database_write(conn);
    break;
  case 'l':
    Database_list(conn);
    break;
  default:
    die("Invalid action, only: c=create, g=get, s=set, d=del, l=list", conn);
  }
  Database_close(conn);

  return 0;
}