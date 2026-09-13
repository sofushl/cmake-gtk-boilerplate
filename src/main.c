#include <gtk/gtk.h>

static void gtk(GtkWidget *widget, gpointer data) { g_print("Hello GTK\n"); }

static void cmake(GtkWidget *widget, gpointer data) {
  g_print("Hello CMake\n");
}

static void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *button;
  GtkWidget *window = gtk_application_window_new(app);
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

  gtk_window_set_title(GTK_WINDOW(window), "Hello World");

  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

  button = gtk_button_new_with_label("GTK");
  g_signal_connect(button, "clicked", G_CALLBACK(gtk), NULL);

  gtk_widget_set_margin_top(button, 20);
  gtk_box_append(GTK_BOX(box), button);

  button = gtk_button_new_with_label("CMake");
  g_signal_connect(button, "clicked", G_CALLBACK(cmake), NULL);
  gtk_box_append(GTK_BOX(box), button);

  button = gtk_button_new_with_label("Exit");
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_window_destroy),
                           window);
  gtk_box_append(GTK_BOX(box), button);

  gtk_widget_set_margin_start(box, 20);
  gtk_widget_set_margin_end(box, 20);
  gtk_window_set_child(GTK_WINDOW(window), box);

  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
  GtkApplication *app =
      gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
