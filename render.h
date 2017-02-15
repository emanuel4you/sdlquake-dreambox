/*
Copyright (C) 1996-1997 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

// refresh.h -- public interface to refresh functions

#define	MAXCLIPPLANES	11

#define	TOP_RANGE		16			// soldier uniform colors
#define	BOTTOM_RANGE	96

//=============================================================================

typedef struct efrag_s
{
	struct mleaf_s		*leaf;
	struct efrag_s		*leafnext;
	struct entity_s		*entity;
	struct efrag_s		*entnext;
} efrag_t;

typedef struct efrag_FPM_s
{
	struct mleaf_FPM_s	*leaf;
	struct efrag_FPM_s	*leafnext;
	struct entity_FPM_s	*entity;
	struct efrag_FPM_s	*entnext;
} efrag_FPM_t;


typedef struct entity_s
{
	qboolean				forcelink;		// model changed

	int						update_type;

	entity_state_t			baseline;		// to fill in defaults in updates

	double					msgtime;		// time of last update
	vec3_t					msg_origins[2];	// last two updates (0 is newest)	
	vec3_t					origin;
	vec3_t					msg_angles[2];	// last two updates (0 is newest)
	vec3_t					angles;	
	struct model_s			*model;			// NULL = no model
	struct efrag_s			*efrag;			// linked list of efrags
	int						frame;
	float					syncbase;		// for client-side animations
	byte					*colormap;
	int						effects;		// light, particals, etc
	int						skinnum;		// for Alias models
	int						visframe;		// last frame this entity was
											//  found in an active leaf
											
	int						dlightframe;	// dynamic lighting
	int						dlightbits;
	
// FIXME: could turn these into a union
	int						trivial_accept;
	struct mnode_s			*topnode;		// for bmodels, first world node
											//  that splits bmodel, or NULL if
											//  not split
} entity_t;

typedef struct entity_FPM_s
{
	qboolean				forcelink;		// model changed

	int						update_type;

	entity_state_FPM_t		baseline;		// to fill in defaults in updates

	double					msgtime;		// time of last update
	vec3_FPM_t				msg_origins[2];	// last two updates (0 is newest)	
	vec3_FPM_t				origin;
	vec3_FPM_t				msg_angles[2];	// last two updates (0 is newest)
	vec3_FPM_t				angles;	
	struct model_FPM_s		*model;			// NULL = no model
	struct efrag_FPM_s		*efrag;			// linked list of efrags
	int						frame;
	float					syncbase;		// for client-side animations
	byte					*colormap;
	int						effects;		// light, particals, etc
	int						skinnum;		// for Alias models
	int						visframe;		// last frame this entity was
											//  found in an active leaf
											
	int						dlightframe;	// dynamic lighting
	int						dlightbits;
	
// FIXME: could turn these into a union
	int						trivial_accept;
	struct mnode_FPM_s		*topnode;		// for bmodels, first world node
											//  that splits bmodel, or NULL if
											//  not split
} entity_FPM_t;

// !!! if this is changed, it must be changed in asm_draw.h too !!!
typedef struct
{
	vrect_t		vrect;				// subwindow in video for refresh
									// FIXME: not need vrect next field here?
	vrect_t		aliasvrect;			// scaled Alias version
	int			vrectright, vrectbottom;	// right & bottom screen coords
	int			aliasvrectright, aliasvrectbottom;	// scaled Alias versions
	float		vrectrightedge;			// rightmost right edge we care about,
										//  for use in edge list
	float		fvrectx, fvrecty;		// for floating-point compares
	float		fvrectx_adj, fvrecty_adj; // left and top edges, for clamping
	int			vrect_x_adj_shift20;	// (vrect.x + 0.5 - epsilon) << 20
	int			vrectright_adj_shift20;	// (vrectright + 0.5 - epsilon) << 20
	float		fvrectright_adj, fvrectbottom_adj;
										// right and bottom edges, for clamping
	float		fvrectright;			// rightmost edge, for Alias clamping
	float		fvrectbottom;			// bottommost edge, for Alias clamping
	float		horizontalFieldOfView;	// at Z = 1.0, this many X is visible 
										// 2.0 = 90 degrees
	float		xOrigin;			// should probably allways be 0.5
	float		yOrigin;			// between be around 0.3 to 0.5

	vec3_t		vieworg;
	vec3_t		viewangles;
	
	float		fov_x, fov_y;

	int			ambientlight;
} refdef_t;

typedef struct
{
	vrect_t		vrect;				// subwindow in video for refresh
									// FIXME: not need vrect next field here?
	vrect_t		aliasvrect;			// scaled Alias version
	int			vrectright, vrectbottom;	// right & bottom screen coords
	int			aliasvrectright, aliasvrectbottom;	// scaled Alias versions
	fixedpoint_t	vrectrightedge;			// rightmost right edge we care about,
										//  for use in edge list
	fixedpoint_t	fvrectx, fvrecty;		// for floating-point compares
	fixedpoint_t	fvrectx_adj, fvrecty_adj; // left and top edges, for clamping
	int			vrect_x_adj_shift20;	// (vrect.x + 0.5 - epsilon) << 20
	int			vrectright_adj_shift20;	// (vrectright + 0.5 - epsilon) << 20
	fixedpoint_t	fvrectright_adj, fvrectbottom_adj;
										// right and bottom edges, for clamping
	fixedpoint_t	fvrectright;			// rightmost edge, for Alias clamping
	fixedpoint_t	fvrectbottom;			// bottommost edge, for Alias clamping
	fixedpoint_t	horizontalFieldOfView;	// at Z = 1.0, this many X is visible 
										// 2.0 = 90 degrees
	fixedpoint_t	xOrigin;			// should probably allways be 0.5
	fixedpoint_t	yOrigin;			// between be around 0.3 to 0.5

	vec3_FPM_t		vieworg;
	vec3_FPM_t		viewangles;
	
	fixedpoint_t	fov_x, fov_y;

	int			ambientlight;
} refdef_FPM_t;


//
// refresh
//
extern	int		reinit_surfcache;


extern	refdef_t	r_refdef;
extern	refdef_FPM_t	r_refdefFPM;

extern vec3_t	r_origin, vpn, vright, vup;

#ifdef USE_PQ_OPT1
extern int	vpn_fxp[3], vright_fxp[3], vup_fxp[3];
extern int	xscale_fxp, yscale_fxp, xcenter_fxp, ycenter_fxp;
extern int		r_refdef_fvrectx_adj_fxp;
extern int		r_refdef_fvrectright_adj_fxp;
extern int		r_refdef_fvrecty_adj_fxp;
extern int		r_refdef_fvrectbottom_adj_fxp;
#endif

extern vec3_FPM_t	r_originFPM, vpnFPM, vrightFPM, vupFPM;

extern	struct texture_s	*r_notexture_mip;


void R_Init (void);
void R_InitFPM (void);
void R_InitTextures (void);
void R_InitEfrags (void);
void R_RenderView (void);		// must set r_refdef first
void R_RenderViewFPM (void);	// must set r_refdefFPM first
void R_ViewChanged (vrect_t *pvrect, int lineadj, float aspect);
void R_ViewChangedFPM (vrect_t *pvrect, int lineadj, fixedpoint_t aspect);
								// called whenever r_refdef or vid change
void R_InitSky (struct texture_s *mt);	// called at level load

void R_AddEfrags (entity_t *ent);
void R_AddEfragsFPM (entity_FPM_t *ent);
void R_RemoveEfrags (entity_t *ent);
void R_RemoveEfragsFPM (entity_FPM_t *ent);

void R_NewMap (void);
void R_NewMapFPM (void);

void R_ParseParticleEffect (void);
void R_ParseParticleEffectFPM (void);
void R_RunParticleEffect (vec3_t org, vec3_t dir, int color, int count);
void R_RunParticleEffectFPM (vec3_FPM_t org, vec3_FPM_t dir, int color, int count);
void R_RocketTrail (vec3_t start, vec3_t end, int type);
void R_RocketTrailFPM (vec3_FPM_t start, vec3_FPM_t end, int type);

#ifdef QUAKE2
void R_DarkFieldParticles (entity_t *ent);
#endif
void R_EntityParticles (entity_t *ent);
void R_EntityParticlesFPM (entity_FPM_t *ent);
void R_BlobExplosion (vec3_t org);
void R_BlobExplosionFPM (vec3_FPM_t org);
void R_ParticleExplosion (vec3_t org);
void R_ParticleExplosionFPM (vec3_FPM_t org);
void R_ParticleExplosion2 (vec3_t org, int colorStart, int colorLength);
void R_ParticleExplosion2FPM (vec3_FPM_t org, int colorStart, int colorLength);
void R_LavaSplash (vec3_t org);
void R_LavaSplashFPM (vec3_FPM_t org);
void R_TeleportSplash (vec3_t org);
void R_TeleportSplashFPM (vec3_FPM_t org);

void R_PushDlights (void);
void R_PushDlightsFPM (void);

//
// surface cache related
//
extern	int		reinit_surfcache;	// if 1, surface cache is currently empty and
extern qboolean	r_cache_thrash;	// set if thrashing the surface cache

int	D_SurfaceCacheForRes (int width, int height);
void D_FlushCaches (void);
void D_FlushCachesFPM (void);
void D_DeleteSurfaceCache (void);
void D_InitCaches (void *buffer, int size);
void R_SetVrect (vrect_t *pvrect, vrect_t *pvrectin, int lineadj);
void R_SetVrectFPM (vrect_t *pvrect, vrect_t *pvrectin, int lineadj);
