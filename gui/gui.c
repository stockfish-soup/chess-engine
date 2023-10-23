#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <ctype.h>
#include <gtk/gtkx.h>
#include "../src/board.h"


GtkWidget *window;
GtkWidget *fixed1;
GtkWidget *chessboard;
GtkBuilder *builder;

Board *board;

GtkWidget *squares[64];
GtkWidget *images[64];

GdkPixbuf *scaled_images[64];
GdkPixbuf *unscaled_images[64];




static void myCSS(void){
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar *myCssFile = "/home/ityder/proj/chess-engine/gui/style.css";
    GError *error = 0;

    gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);

    if (error) {
        // Display a warning if the stylesheet is not loaded
        g_warning ("%s", error->message);

        // Free the memory allocated for the error
        // and acknowledge the error has been processed
        g_clear_error (&error);
    }

    g_object_unref (provider);
}

void css_set(GtkCssProvider * provider, GtkWidget *g_widget, const gchar *style) {
    GtkStyleContext *context;
    context = gtk_widget_get_style_context(g_widget);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider),1000);
    gtk_style_context_add_class(context, style);
}


int main(int argc, char *argv[]) {

    gtk_init(&argc, &argv); // init Gtk

    // myCSS();


    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar *myCssFile = "style.css";
    GError *error = 0;

    gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);
    g_object_unref (provider);
    
    // establish contact with xml code 

    builder = gtk_builder_new_from_file ("gui.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder,"window"));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_builder_connect_signals(builder, NULL);

    fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
    chessboard = GTK_WIDGET(gtk_builder_get_object(builder, "chessboard"));

    int i;

    GdkColor white_color;
    GdkColor black_color;

    gdk_color_parse( "#fad0a0", &white_color );
    gdk_color_parse( "#a26622", &black_color );

    GError *err;

    int pieces[64];


    for (i=0; i<64; i++) {

      pieces[i] = wK;

      // get the str of squares

      char sq_nb_str[10];
      char sq_name[10] = "s";

      sprintf(sq_nb_str, "%d", i);

      strcat(sq_name,sq_nb_str);

      // and images

      char i_nb_str[10];
      char i_name[10] = "i";

      sprintf(i_nb_str, "%d", i);

      strcat(i_name,i_nb_str);

      squares[i] = GTK_WIDGET(gtk_builder_get_object(builder, sq_name));
      images[i] = GTK_WIDGET(gtk_builder_get_object(builder, i_name));

      err = NULL;

      if (i%2 == 0 && i%16 < 8 || i%2 == 1 && i%16 >= 8) {

        // black squares

        // gtk_widget_set_name(squares[i], "black_button");

        css_set(provider, squares[i],"black_square");

      } else {

        // white squares 

        // gtk_widget_set_name(squares[i], "white_button");

        css_set(provider, squares[i],"white_square");

      }

      switch (pieces[i]) {
        case wP:
          unscaled_images[i] = gdk_pixbuf_new_from_file("pieces/wP.svg",&err);
          break;
        case wN:
          unscaled_images[i] = gdk_pixbuf_new_from_file("pieces/wN.svg",&err);
          break;
        case wB:
          unscaled_images[i] = gdk_pixbuf_new_from_file("pieces/wB.svg",&err);
          break;
        case wR:
          unscaled_images[i] = gdk_pixbuf_new_from_file("pieces/wR.svg",&err);
          break;
        case wQ:
          unscaled_images[i] = gdk_pixbuf_new_from_file("pieces/wQ.svg",&err);
          break;
        case wK:
          unscaled_images[i] = gdk_pixbuf_new_from_file("pieces/wK.svg",&err);
          break;
        case bP:
          unscaled_images[i] = gdk_pixbuf_new_from_file("pieces/bP.svg",&err);
          break;
        case bN:
          unscaled_images[i] = gdk_pixbuf_new_from_file("pieces/bN.svg",&err);
          break;
        case bB:
          unscaled_images[i] = gdk_pixbuf_new_from_file("pieces/bB.svg",&err);
          break;
        case bR:
          unscaled_images[i] = gdk_pixbuf_new_from_file("pieces/bR.svg",&err);
          break;
        case bQ:
          unscaled_images[i] = gdk_pixbuf_new_from_file("pieces/bQ.svg",&err);
          break;
        case bK:
          unscaled_images[i] = gdk_pixbuf_new_from_file("pieces/bK.svg",&err);
          break;
        default:
          unscaled_images[i] = gdk_pixbuf_new_from_file("pieces/EMPTY.svg",&err);
          break;

      }

      scaled_images[i] = gdk_pixbuf_scale_simple(unscaled_images[i],60,75,GDK_INTERP_NEAREST);
      gtk_image_set_from_pixbuf(images[i],scaled_images[i]);

    }

    gtk_widget_show_all(window);

    gtk_main();

    return EXIT_SUCCESS;

}

