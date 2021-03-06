#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <faux/str.h>
#include <klish/ktp_session.h>

#include "private.h"


ktp_session_t *ktp_session_new(int sock)
{
	ktp_session_t *session = NULL;

	if (sock < 0)
		return NULL;

	session = faux_zmalloc(sizeof(*session));
	assert(session);
	if (!session)
		return NULL;

	// Init
	session->state = KTP_SESSION_STATE_NOT_AUTHORIZED;
	session->net = faux_net_new();
	assert(session->net);
	faux_net_set_fd(session->net, sock);

	return session;
}


void ktp_session_free(ktp_session_t *session)
{
	if (!session)
		return;

	faux_net_free(session->net);
	faux_free(session);
}


bool_t ktp_session_connected(ktp_session_t *session)
{
	assert(session);
	if (!session)
		return BOOL_FALSE;
	if (KTP_SESSION_STATE_DISCONNECTED == session->state)
		return BOOL_FALSE;

	return BOOL_TRUE;
}


int ktp_session_get_socket(ktp_session_t *session)
{
	assert(session);
	if (!session)
		return BOOL_FALSE;

	return faux_net_get_fd(session->net);
}


#if 0
static void ktp_session_bad_socket(ktp_session_t *session)
{
	assert(session);
	if (!session)
		return;

	session->state = KTP_SESSION_STATE_DISCONNECTED;
}
#endif
