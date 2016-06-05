var app = angular.module('BlogPosts', []);

app.controller('websiteController', function($scope, $http){
	$scope.titleTemplateUrl = "client/template/title.html";
	$scope.blogPostTemplateUrl = "client/template/blogPost.html";
	$scope.sidebarTemplateUrl = "client/template/sidebar.html";
	$scope.footerTemplateUrl = "client/template/footer.html";
})

app.controller('titleController', function($scope, $http){
	$scope.websiteTitle = "Website Test";
	$scope.websiteTagline = "The clean website look we all need but don't deserve";
})

app.controller('mainContentController', function($scope, $http) {
   $scope.posts = [
		{
			title: "This is an article",
			author: "James",
			pubdate: "Monday, 30th of May",
			
			media: "media/grass.jpg",
			content: "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed at libero urna. Praesent auctor vestibulum eros, pretium ultrices quam vulputate in. Phasellus pretium purus massa, vel feugiat lacus eleifend non. Proin porta, lacus pulvinar lobortis luctus, tortor lorem sollicitudin dolor, placerat pharetra nisl sapien nec lectus. Aliquam erat volutpat. Proin auctor dapibus quam, eget tristique nunc pretium a. Vivamus ut elit felis. Suspendisse suscipit molestie vulputate. Aenean purus purus, tempus a urna sollicitudin, tempus varius sapien.",
			comments: 2
		},
		{
			title: "This is an article",
			author: "James",
			pubdate: "Monday, 30th of May",
			
			media: "media/splash.jpg",
			content: "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed at libero urna. Praesent auctor vestibulum eros, pretium ultrices quam vulputate in. Phasellus pretium purus massa, vel feugiat lacus eleifend non. Proin porta, lacus pulvinar lobortis luctus, tortor lorem sollicitudin dolor, placerat pharetra nisl sapien nec lectus. Aliquam erat volutpat. Proin auctor dapibus quam, eget tristique nunc pretium a. Vivamus ut elit felis. Suspendisse suscipit molestie vulputate. Aenean purus purus, tempus a urna sollicitudin, tempus varius sapien.",
			comments: 50
		},
		{
			title: "This is an article",
			author: "James",
			pubdate: "Monday, 30th of May",
			
			media: "media/sunset.jpg",
			content: "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed at libero urna. Praesent auctor vestibulum eros, pretium ultrices quam vulputate in. Phasellus pretium purus massa, vel feugiat lacus eleifend non. Proin porta, lacus pulvinar lobortis luctus, tortor lorem sollicitudin dolor, placerat pharetra nisl sapien nec lectus. Aliquam erat volutpat. Proin auctor dapibus quam, eget tristique nunc pretium a. Vivamus ut elit felis. Suspendisse suscipit molestie vulputate. Aenean purus purus, tempus a urna sollicitudin, tempus varius sapien.",
			comments: 2
		}
   ];
});

app.controller('footerController', function($scope, $http){
	$scope.footerCopyrightNotice = "Copyright (C) James R Swift, 2016";
})