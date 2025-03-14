
#define CONTROLS 4

#define GUI_ELEMENTS 0

#define TAB_ELEMENTS 0


#define PLUGIN_UI_URI "urn:brummer:PowerAmpImpulses_ui"


#include "lv2_plugin.h"


#include "xresources.h"

void set_costum_theme(Widget_t *w) {
    w->color_scheme->normal = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .fg =       { 0.850, 0.850, 0.850, 1.000},
        .bg =       { 0.100, 0.100, 0.100, 1.000},
        .base =     { 0.000, 0.000, 0.000, 1.000},
        .text =     { 0.900, 0.900, 0.900, 1.000},
        .shadow =   { 0.000, 0.000, 0.000, 0.200},
        .frame =    { 0.000, 0.000, 0.000, 1.000},
        .light =    { 0.100, 0.100, 0.100, 1.000}
    };

    w->color_scheme->prelight = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .fg =       { 1.000, 0.000, 1.000, 1.000},
        .bg =       { 0.250, 0.250, 0.250, 1.000},
        .base =     { 0.300, 0.300, 0.300, 1.000},
        .text =     { 1.000, 1.000, 1.000, 1.000},
        .shadow =   { 0.100, 0.100, 0.100, 0.400},
        .frame =    { 0.300, 0.300, 0.300, 1.000},
        .light =    { 0.300, 0.300, 0.300, 1.000}
    };

    w->color_scheme->selected = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .fg =       { 0.900, 0.900, 0.900, 1.000},
        .bg =       { 0.200, 0.200, 0.200, 1.000},
        .base =     { 0.500, 0.180, 0.180, 1.000},
        .text =     { 1.000, 1.000, 1.000, 1.000},
        .shadow =   { 0.800, 0.180, 0.180, 0.200},
        .frame =    { 0.500, 0.180, 0.180, 1.000},
        .light =    { 0.500, 0.180, 0.180, 1.000}
    };

    w->color_scheme->active = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .fg =       { 0.000, 1.000, 1.000, 1.000},
        .bg =       { 0.000, 0.000, 0.000, 1.000},
        .base =     { 0.180, 0.380, 0.380, 1.000},
        .text =     { 0.750, 0.750, 0.750, 1.000},
        .shadow =   { 0.180, 0.380, 0.380, 0.500},
        .frame =    { 0.180, 0.380, 0.380, 1.000},
        .light =    { 0.180, 0.380, 0.380, 1.000}
    };

    w->color_scheme->insensitive = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .fg =       { 0.850, 0.850, 0.850, 0.500},
        .bg =       { 0.100, 0.100, 0.100, 0.500},
        .base =     { 0.000, 0.000, 0.000, 0.500},
        .text =     { 0.900, 0.900, 0.900, 0.500},
        .shadow =   { 0.000, 0.000, 0.000, 0.100},
        .frame =    { 0.000, 0.000, 0.000, 0.500},
        .light =    { 0.100, 0.100, 0.100, 0.500}
    };
}

#include "lv2_plugin.cc"



void plugin_value_changed(X11_UI *ui, Widget_t *w, PortIndex index) {
    // do special stuff when needed
}

void plugin_set_window_size(int *w,int *h,const char * plugin_uri, float scale) {
    (*w) = 503 * scale; //set initial width of main window
    (*h) = 200 * scale; //set initial height of main window
}

const char* plugin_set_name() {
    return "PowerAmpImpulses"; //set plugin name to display on UI
}

void plugin_create_controller_widgets(X11_UI *ui, const char * plugin_uri, float scale) {
    set_costum_theme(ui->win);
    ui->widget[0] = add_lv2_image_toggle (ui->widget[0], ui->win, 2, "Bypass", ui, 60,  60, 60 * scale, 80 * scale);
    widget_get_png(ui->widget[0], LDVAR(switch_gbxc_png));

    ui->widget[1] = add_lv2_knob (ui->widget[1], ui->win, 3, "INPUT", ui, 140,  60, 60 * scale, 80 * scale);
    widget_get_png(ui->widget[1], LDVAR(knob_sprite_caccaebi_png));
    set_adjustment(ui->widget[1]->adj, 0.0, 0.0, -20.0, 20.0, 0.1, CL_CONTINUOS);

    ui->widget[2] = add_lv2_knob (ui->widget[2], ui->win, 4, "OUTPUT", ui, 210,  60, 60 * scale, 80 * scale);
    widget_get_png(ui->widget[2], LDVAR(knob_sprite_caccaebi_png));
    set_adjustment(ui->widget[2]->adj, 0.0, 0.0, -20.0, 20.0, 0.1, CL_CONTINUOS);

    ui->widget[3] = add_lv2_combobox (ui->widget[3], ui->win, 5, "", ui, 309,  81, 150 * scale, 30 * scale);
    combobox_add_entry (ui->widget[3], "Blackat Leon");
    combobox_add_entry (ui->widget[3], "Cicognani Imperivm Luxury");
    combobox_add_entry (ui->widget[3], "DV Mark Triple 6");
    combobox_add_entry (ui->widget[3], "Engl Retro Tube");
    combobox_add_entry (ui->widget[3], "Engl Special Edition");
    combobox_add_entry (ui->widget[3], "EVH 5150 III");
    combobox_add_entry (ui->widget[3], "Fortin Natas");
    combobox_add_entry (ui->widget[3], "Kaos Sludge 15");
    combobox_add_entry (ui->widget[3], "Krank Krankenstein");
    combobox_add_entry (ui->widget[3], "Laney ironheart");
    combobox_add_entry (ui->widget[3], "MakosampCustomHatred");
    combobox_add_entry (ui->widget[3], "Marshall JMP 2203");
    combobox_add_entry (ui->widget[3], "Marshall MG 15");
    combobox_add_entry (ui->widget[3], "Mesa Boogie Mark V");
    combobox_add_entry (ui->widget[3], "Peavey Vypyr 15");
    combobox_add_entry (ui->widget[3], "Randall Satan");
    combobox_add_entry (ui->widget[3], "Randall thrasher");
    combobox_add_entry (ui->widget[3], "Splawn Nitro");
    combobox_add_entry (ui->widget[3], "Splawn Quick Rod");
    combobox_add_entry (ui->widget[3], "Taurus Stomphead");
    set_adjustment(ui->widget[3]->adj, 0.0, 0.0, 0.0, 19.0, 1.0, CL_ENUM);

}

void plugin_cleanup(X11_UI *ui) {
    // clean up used sources when needed
}


void plugin_port_event(LV2UI_Handle handle, uint32_t port_index,
                        uint32_t buffer_size, uint32_t format,
                        const void * buffer) {
    // port value change message from host
    // do special stuff when needed
}

