/*************************************************************************/
/*  websocket_server.cpp                                                 */
/*************************************************************************/
/*                       This file is part of:                           */
/*                      GODOT WEBSOCKET MODULE                           */
/*            https://github.com/LudiDorici/godot-websocket              */
/*************************************************************************/
/* Copyright (c) 2017 Ludi Dorici, di Alessandrelli Fabio                */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/
#include "websocket_server.h"

GDCINULL(WebSocketServer);

WebSocketServer::WebSocketServer() {
	_peer_id = 1;
}

WebSocketServer::~WebSocketServer() {
}

void WebSocketServer::_bind_methods() {

	ClassDB::bind_method(D_METHOD("is_listening"), &WebSocketServer::is_listening);
	ClassDB::bind_method(D_METHOD("listen", "port", "protocols", "gd_mp_api"), &WebSocketServer::listen, DEFVAL(PoolVector<String>()), DEFVAL(false));
	ClassDB::bind_method(D_METHOD("stop"), &WebSocketServer::stop);
	ClassDB::bind_method(D_METHOD("has_peer", "id"), &WebSocketServer::has_peer);
	ClassDB::bind_method(D_METHOD("get_protocols"), &WebSocketServer::get_protocols);

	ADD_SIGNAL(MethodInfo("client_disconnected", PropertyInfo(Variant::INT, "id")));
	ADD_SIGNAL(MethodInfo("client_connected", PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::STRING, "protocol")));
	ADD_SIGNAL(MethodInfo("data_received", PropertyInfo(Variant::INT, "id")));
}

NetworkedMultiplayerPeer::ConnectionStatus WebSocketServer::get_connection_status() const {
	if (is_listening())
		return CONNECTION_CONNECTED;

	return CONNECTION_DISCONNECTED;
};

bool WebSocketServer::is_server() const {

	return true;
}

void WebSocketServer::_on_peer_packet(int32_t p_peer_id) {

	if (_is_multiplayer) {
		_process_multiplayer(get_peer(p_peer_id), p_peer_id);
	} else {
		emit_signal("data_received", p_peer_id);
	}
}

void WebSocketServer::_on_connect(int32_t p_peer_id, String p_protocol) {

	if (_is_multiplayer) {
		// Send add to clients
		_send_add(p_peer_id);
		emit_signal("peer_connected", p_peer_id);
	} else {
		emit_signal("client_connected", p_peer_id, p_protocol);
	}
}

void WebSocketServer::_on_disconnect(int32_t p_peer_id) {

	if (_is_multiplayer) {
		// Send delete to clients
		_send_del(p_peer_id);
		emit_signal("peer_disconnected", p_peer_id);
	} else {
		emit_signal("client_disconnected", p_peer_id);
	}
}
