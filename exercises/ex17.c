#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

struct Address {
  int id;
  int set;
  char *name;
  char *email;
};

struct Database {
  size_t max_rows;
  size_t max_data;
  struct Address *rows;
};

struct Connection {
  FILE *file;
  struct Database *db;
};

void Database_close(struct Connection *conn) {
  if (conn) {
    for (size_t i = 0; i < conn->db->max_rows; i++) {
      struct Address *row = &conn->db->rows[i];

      if (row->name)
        free(row->name);
      if (row->email)
        free(row->email);
    }

    if (conn->file)
      fclose(conn->file);
    if (conn->db)
      free(conn->db);
    free(conn);
  }
}

void die(const char *message, struct Connection *conn) {
  if (errno) {
    perror(message);
  } else {
    printf("ERROR: %s\n", message);
  }
  Database_close(conn);
  exit(1);
}

void Address_print(struct Address *addr) {
  printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn) {
  assert(conn->db && conn->file);

  if (fread(conn->db, sizeof(struct Database), 1, conn->file) != 1)
    die("Failed to load database", conn);

  conn->db->rows = malloc(sizeof(struct Address) * conn->db->max_rows);

  for (size_t i = 0; i < conn->db->max_rows; i++) {
    struct Address *row = &conn->db->rows[i];
    if (fread(&row->id, sizeof(int), 1, conn->file) != 1)
      die("Failed to load id.", conn);
    if (fread(&row->set, sizeof(int), 1, conn->file) != 1)
      die("Failed to load set.", conn);

    row->name = malloc(conn->db->max_data);
    row->email = malloc(conn->db->max_data);
    if (fread(row->name, conn->db->max_data, 1, conn->file) != 1)
      die("Failed to load name", conn);
    if (fread(row->email, conn->db->max_data, 1, conn->file) != 1)
      die("Failed to load email", conn);
  }
}

struct Connection *Database_open(const char *filename, char mode) {
  struct Connection *conn = malloc(sizeof(struct Connection));
  if (!conn)
    die("Memory error", conn);

  conn->db = malloc(sizeof(struct Database));
  if (!conn->db)
    die("Memory error", conn);

  if (mode == 'c') {
    conn->file = fopen(filename, "w");
  } else {
    conn->file = fopen(filename, "r+");

    if (conn->file)
      Database_load(conn);
  }
  if (!conn->file)
    die("Failed to open the file", conn);

  return conn;
}

void Database_write(struct Connection *conn) {
  rewind(conn->file);
  if (fwrite(conn->db, sizeof(struct Database), 1, conn->file) != 1)
    die("Failed to write database", conn);

  for (size_t i = 0; i < conn->db->max_rows; i++) {
    if (fwrite(&((conn->db->rows[i]).id), sizeof(int), 1, conn->file) != 1)
      die("Failed to write id.", conn);
    if (fwrite(&((conn->db->rows[i]).set), sizeof(int), 1, conn->file) != 1)
      die("Failed to write set.", conn);
    if (fwrite((conn->db->rows[i]).name, conn->db->max_data, 1, conn->file) !=
        1)
      die("Failed to write name.", conn);
    if (fwrite((conn->db->rows[i]).email, conn->db->max_data, 1, conn->file) !=
        1)
      die("Failed to write email.", conn);
  }

  if (fflush(conn->file) == -1)
    die("Cannot flush database", conn);
}

void Database_create(struct Connection *conn) {
  int max_rows, max_data;
  printf("max_rows: ");
  scanf("%d", &max_rows);
  printf("max_data: ");
  scanf("%d", &max_data);
  conn->db->max_rows = max_rows;
  conn->db->max_data = max_data;

  conn->db->rows =
      (struct Address *)malloc(sizeof(struct Address) * conn->db->max_rows);

  for (size_t i = 0; i < conn->db->max_rows; i++) {
    char *name = (char *)malloc(conn->db->max_data);
    memset(name, 0, conn->db->max_data);
    char *email = (char *)malloc(conn->db->max_data);
    memset(email, 0, conn->db->max_data);
    struct Address addr = {.id = i, .set = 0, .name = name, .email = email};
    conn->db->rows[i] = addr;
  }
}

void Database_set(struct Connection *conn, int id, char *name, char *email) {
  struct Address *addr = &conn->db->rows[id];
  if (addr->set)
    die("Already set delete it frist", conn);

  name[MAX_DATA - 1] = '\0';
  char *res = strncpy(addr->name, name, MAX_DATA);
  if (!res)
    die("Name copy failed", conn);

  email[MAX_DATA - 1] = '\0';
  res = strncpy(addr->email, email, MAX_DATA);
  if (!res)
    die("Email copy failed", conn);
  addr->set = 1;
}

void Database_get(struct Connection *conn, int id) {
  struct Address *addr = &conn->db->rows[id];
  if (addr->set) {
    Address_print(addr);
  } else {
    die("ID is not set", conn);
  }
}

void Database_delete(struct Connection *conn, int id) {
  char *name = (char *)malloc(conn->db->max_data);
  memset(name, 0, conn->db->max_data);
  char *email = (char *)malloc(conn->db->max_data);
  memset(email, 0, conn->db->max_data);
  struct Address addr = {.id = id, .set = 0, .name = name, .email = email};
  conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn) {
  struct Database *db = conn->db;
  for (int i = 0; i < conn->db->max_rows; i++) {
    struct Address *cur = &db->rows[i];
    if (cur->set) {
      Address_print(cur);
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc < 3)
    die("USAGE: ex17 <dbfile> <action> [action params]", NULL);
  int id = 0;
  if (argc > 3)
    id = atoi(argv[3]);

  char *filename = argv[1];
  char action = argv[2][0];
  struct Connection *conn = Database_open(filename, action);

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