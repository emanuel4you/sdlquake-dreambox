###############################################################################
# Makefile for OpenWrt-Zipit Quake.
###############################################################################
PROGRAM = sdlquake
ALL_LIBS += `pkg-config --libs sdl` -lm
# list all .c files here
CFILES	=					cd_null.c \
						vid_sdl.c \
						snd_sdl.c \
						sys_sdl.c \
						net_none.c \
						chase.c \
						cl_demo.c \
						cl_input.c \
						cl_main.c \
						cl_parse.c \
						cl_tent.c \
						cmd.c \
						common.c \
						console.c \
						crc.c \
						cvar.c \
						d_edge.c \
						d_fill.c \
						d_init.c \
						d_modech.c \
						d_part.c \
						d_polyse.c \
						d_scan.c \
						d_sky.c \
						d_sprite.c \
						d_surf.c \
						d_vars.c \
						d_zpoint.c \
						draw.c \
						FixedPointMath.c \
						host.c \
						host_cmd.c \
						keys.c \
						mathlib.c \
						menu.c \
						model.c \
						net_dgrm.c \
						net_loop.c \
						net_main.c \
						net_vcr.c \
						nonintel.c \
						pr_cmds.c \
						pr_edict.c \
						pr_exec.c \
						r_aclip.c \
						r_alias.c \
						r_bsp.c \
						r_draw.c \
						r_edge.c \
						r_efrag.c \
						r_light.c \
						r_main.c \
						r_misc.c \
						r_part.c \
						r_sky.c \
						r_sprite.c \
						r_surf.c \
						r_vars.c \
						sbar.c \
						screen.c \
						snd_dma.c \
						snd_mix.c \
						sv_main.c \
						sv_move.c \
						sv_phys.c \
						sv_user.c \
						snd_mem.c \
						view.c \
						wad.c \
						world.c \
						zone.c

##############################################################################
# You shouldn't need to change anything below here, really
##############################################################################
CFLAGS += -Wall -pipe -c -ffast-math -funroll-loops -falign-loops=2 -falign-jumps=2 -falign-functions=2 -fno-strict-aliasing `pkg-config --cflags sdl`
LDFLAGS += -s

OFILES  =       $(SFILES:.S=.o) $(CFILES:.c=.o)

$(PROGRAM): $(OFILES)
	$(CC) $(OFILES) $(LDFLAGS) $(LIBDIRS) $(ALL_LIBS) -o $@

.PHONY: all clean

all:		$(PROGRAM)

%.o:	%.c
	$(CC) $(ALL_INCLUDES) $(CFLAGS) -c $< -o $@

%.o:	%.S
	$(CC) $(ALL_INCLUDES) $(CFLAGS) -c $< -o $@

clean:
	-rm -f $(OFILES) $(MAPFILE) $(PROGRAM)
