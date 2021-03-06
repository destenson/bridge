/*
 * Testing of websocket connectivity
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "utils/websocket.h"

int test_connect() {
	struct WebSocketClient *ws;
	char* host = "127.0.0.1";
	char* service = "8090";
	char* path = "/";
	char buf[4096];
	char *tst_json[] = {
		"{\"method\": \"call\", \"params\": [1, \"login\", [\"\", \"\"]], \"id\": 1}",
		"{\"method\": \"call\", \"params\": [1, \"database\", []], \"id\": 2}",
		"{\"method\": \"call\", \"params\": [1, \"history\", []], \"id\": 3}",
		"{\"method\": \"call\", \"params\": [2, \"set_subscribe_callback\", [5, false]], \"id\": 4}",
		"{\"method\": \"call\", \"params\": [2, \"get_objects\", [[\"2.1.0\"]]], \"id\": 5}",
		NULL };
	int i, timeout = 60;

	ws = websocket_connect(host, service, path);
	if (!ws) {
		return 0;
	}
	for (i = 0 ; tst_json[i] ; i++) {
		fprintf (stderr, "> %s\n", tst_json[i]);
		if (websocket_call(ws, tst_json[i], buf, sizeof(buf), timeout) > 0) {
			fprintf (stderr, "< %s\n", buf);
		} else {
			return 0;
		}
	}
	websocket_client_free (ws);
	return 1;
}
