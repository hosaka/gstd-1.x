/*
 * GStreamer Daemon - Gst Launch under steroids
 * Copyright (c) 2015-2018 Ridgerun, LLC (http://www.ridgerun.com)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */
#include <gst/check/gstcheck.h>
#include <string.h>

#include "libgstc.h"
#include "libgstc_socket.h"

static gchar _request[512];

/* Mock implementation of a socket */
typedef struct _GstcSocket
{
} GstcSocket;

GstcSocketStatus
gstc_socket_send (GstcSocket *socket, const gchar *request)
{
  memcpy (_request, request, strlen(request));

  return GSTC_SOCKET_OK;
}

GST_START_TEST (test_pipeline_create)
{
  GstClient *client;
  GstcStatus ret;
  
  const gchar * address = "";
  const unsigned int port = 0;
  const unsigned long wait_time = 0;
  const int keep_connection_open = 0;

  const gchar * pipeline_name = "pipe";
  const gchar * pipeline_desc = "fakesrc ! fakesink";
  const gchar * expected = "create /pipelines pipe fakesrc ! fakesink";
  
  client = gstc_client_new (address, port, wait_time, keep_connection_open);

  ret = gstc_pipeline_create (client, pipeline_name, pipeline_desc);
  fail_if (GSTC_OK != ret);

  assert_equals_string (expected, _request);
  
  gstc_client_free (client);
}

GST_END_TEST;

static Suite *
libgstc_pipeline_suite (void)
{
  Suite *suite = suite_create ("libgstc_pipeline");
  TCase *tc = tcase_create ("general");

  suite_add_tcase (suite, tc);
  tcase_add_test (tc, test_pipeline_create);

  return suite;
}

GST_CHECK_MAIN (libgstc_pipeline);