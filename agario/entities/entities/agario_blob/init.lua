
AddCSLuaFile( "shared.lua" )
AddCSLuaFile( "cl_init.lua" )
include( "cl_init.lua" )

function ENT:Initialize()
	
	-- Use the helibomb model just for the shadow (because it's about the same size)
	self:SetModel( "models/Combine_Helicopter/helicopter_bomb01.mdl" )
	
	self:SetupCustomPhysics( self:GetBallSize() )
	self:SetBlobColor( Vector( 1, 0.3, 0.3 ) )
	self:NetworkVarNotify( "BlobSize", self.OnBlobSizeChanged )

end

function ENT:OnBlobSizeChanged( varname, oldvalue, newvalue )
		
	self:SetupCustomPhysics( self:GetBlobSize() )

end

function ENT:SetupCustomPhysics( size )

	self:PhysicsInitSphere( size / 2.1, "metal_bouncy" )
	--self:PhysicsInitConvex( table points )
	
	local phys = self:GetPhysicsObject()
	if ( IsValid( phys ) ) then
		phys:Wake()
	end

end