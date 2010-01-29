#ifndef RESOURCEGROUP_H_
#define RESOURCEGROUP_H_

#include <wx/wx.h>
#include <wx/treectrl.h>

enum ResourceType
{
	RESTYPE_TEXTURE,
	RESTYPE_MESH,
	RESTYPE_MODEL,
	RESTYPE_TERRAIN
};

struct ResourceGroup
{
	ResourceGroup (ResourceType _type, const wxString& _name)
	{
		name = _name;
		type = _type;
	}

	wxString		name;
	wxIcon			icon;
	wxTreeItemId	item;
	ResourceType	type;
};


struct ResourceItem : public wxTreeItemData
{
	ResourceItem (ResourceType _type, const wxString& _name)
	{
		name = _name;
		type = _type;
	}

	wxString		name;
	ResourceType	type;
};

#endif