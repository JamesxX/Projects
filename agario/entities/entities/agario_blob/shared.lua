
DEFINE_BASECLASS( "base_anim" )

ENT.Editable		= true
ENT.Spawnable		= false
ENT.AdminOnly		= false
ENT.RenderGroup		= RENDERGROUP_TRANSLUCENT

function ENT:SetupDataTables()

	self:NetworkVar( "Float", 0, "BlobSize", { KeyName = "blobsize", Edit = { type = "Float", min = 4, max = 128, order = 1 } } )
	self:NetworkVar( "Vector", 0, "BlobColor", { KeyName = "blobcolor", Edit = { type = "VectorColor", order = 2 } } )

end
