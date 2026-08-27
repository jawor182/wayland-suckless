#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "idle-inhibit.h"
#include <wayland-client-protocol.h>
#include <wayland-client.h>

struct State {
  struct wl_display *display;
  struct wl_registry *registry;

  struct wl_surface *surface;
  struct wl_compositor *compositor;

  struct zwp_idle_inhibit_manager_v1 *idle_inhibit_manager;
};

static void registry_global(void *data, struct wl_registry *registry,
                            uint32_t name, const char *interface,
                            uint32_t version) {
  struct State *state = data;

  if (strcmp(interface, zwp_idle_inhibit_manager_v1_interface.name) == 0) {
    state->idle_inhibit_manager = wl_registry_bind(
        registry, name, &zwp_idle_inhibit_manager_v1_interface, 1);
  } else if (strcmp(interface, wl_compositor_interface.name) == 0) {
    state->compositor =
        wl_registry_bind(registry, name, &wl_compositor_interface, 1);
  }
}

static void registry_global_remove(void *data, struct wl_registry *registry,
                                   uint32_t name) {}

static const struct wl_registry_listener registry_listener = {
    .global = registry_global,
    .global_remove = registry_global_remove,
};

int main(void) {
  struct State state = {0};

  state.display = wl_display_connect(NULL);

  if (!state.display) {
    fprintf(stderr, "Failed to connect to Wayland display\n");
    return 1;
  }

  state.registry = wl_display_get_registry(state.display);

  wl_registry_add_listener(state.registry, &registry_listener, &state);

  /*
   * The registry events haven't necessarily been received yet.
   * Force a round trip so registry_global() gets called.
   */
  wl_display_roundtrip(state.display);

  state.surface = wl_compositor_create_surface(state.compositor);

  if (!state.idle_inhibit_manager) {
    fprintf(stderr, "Compositor does not support idle inhibition\n");
    wl_display_disconnect(state.display);
    return 1;
  }

  printf("Inhibiting idle program...\n");

  struct zwp_idle_inhibitor_v1 *inhibitor =
      zwp_idle_inhibit_manager_v1_create_inhibitor(state.idle_inhibit_manager,
                                                   state.surface);

  while (wl_display_dispatch(state.display) != -1) {
  }
  wl_display_disconnect(state.display);
  return 0;
}
