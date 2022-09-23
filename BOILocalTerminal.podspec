#
# Be sure to run `pod lib lint BOILocalTerminal.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'BOILocalTerminal'
  s.version          = '0.1.0'
  s.summary          = 'A short description of BOILocalTerminal.'

# This description is used to generate tags and improve search results.
#   * Think: What does it do? Why did you write it? What is the focus?
#   * Try to keep it short, snappy and to the point.
#   * Write the description between the DESC delimiters below.
#   * Finally, don't worry about the indent, CocoaPods strips it!

  s.description      = <<-DESC
TODO: Add long description of the pod here.
                       DESC

  s.homepage         = 'https://github.com/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/BOILocalTerminal'
  # s.screenshots     = 'www.example.com/screenshots_1', 'www.example.com/screenshots_2'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { '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' => 'eldhose@isletsystems.com' }
  s.source           = { :git => 'https://github.com/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/BOILocalTerminal.git', :tag => s.version.to_s }
  # s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'

  s.ios.deployment_target = '10.0'

  s.source_files = 'BOILocalTerminal/Classes/**/*'
  
  # s.resource_bundles = {
  #   'BOILocalTerminal' => ['BOILocalTerminal/Assets/*.png']
  # }

  # s.public_header_files = 'Pod/Classes/**/*.h'
  # s.frameworks = 'UIKit', 'MapKit'
  # s.dependency 'AFNetworking', '~> 2.3'
end
